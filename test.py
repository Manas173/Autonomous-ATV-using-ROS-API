
# coding: utf-8

# # Object Detection Demo
# Welcome to the object detection inference walkthrough!  This notebook will walk you step by step through the process of using a pre-trained model to detect objects in an image. Make sure to follow the [installation instructions](https://github.com/tensorflow/models/blob/master/research/object_detection/g3doc/installation.md) before you start.

# # Imports

# In[1]:

import rospy
import numpy as np
from matplotlib import pyplot as plt
import os
import six.moves.urllib as urllib
import sys
import tarfile
import tensorflow as tf
import zipfile
from std_msgs.msg import Int32

from collections import defaultdict
from io import StringIO

from PIL import Image
import cv2
turn=1
cap = cv2.VideoCapture(1)
rospy.init_node("chatter007",anonymous=True)
pub=rospy.Publisher("node",Int32,queue_size=10)
# This is needed since the notebook is stored in the object_detection folder.
sys.path.append("..")
from object_detection.utils import ops as utils_ops

if tf.__version__ < '1.4.0':
  raise ImportError('Please upgrade your tensorflow installation to v1.4.* or later!')


# ## Env setup

# In[ ]:





# ## Object detection imports
# Here are the imports from the object detection module.

# In[ ]:


from utils import label_map_util

from utils import visualization_utils as vis_util


# # Model preparation 

# ## Variables
# 
# Any model exported using the `export_inference_graph.py` tool can be loaded here simply by changing `PATH_TO_CKPT` to point to a new .pb file.  
# 
# By default we use an "SSD with Mobilenet" model here. See the [detection model zoo](https://github.com/tensorflow/models/blob/master/research/object_detection/g3doc/detection_model_zoo.md) for a list of other models that can be run out-of-the-box with varying speeds and accuracies.

# In[ ]:


# What model to download.
MODEL_NAME = 'ssd_mobilenet_v1_coco_2017_11_17'
MODEL_FILE = MODEL_NAME + '.tar.gz'
DOWNLOAD_BASE = 'http://download.tensorflow.org/models/object_detection/'

# Path to frozen detection graph. This is the actual model that is used for the object detection.
PATH_TO_CKPT = MODEL_NAME + '/frozen_inference_graph.pb'

# List of the strings that is used to add correct label for each box.
PATH_TO_LABELS = os.path.join('data', 'mscoco_label_map.pbtxt')

NUM_CLASSES = 90

rate_1=rospy.Rate(10)
# ## Download Model

# In[ ]:


opener = urllib.request.URLopener()
opener.retrieve(DOWNLOAD_BASE + MODEL_FILE, MODEL_FILE)
tar_file = tarfile.open(MODEL_FILE)
for file in tar_file.getmembers():
  file_name = os.path.basename(file.name)
  if 'frozen_inference_graph.pb' in file_name:
    tar_file.extract(file, os.getcwd())


# ## Load a (frozen) Tensorflow model into memory.

# In[ ]:


detection_graph = tf.Graph()
with detection_graph.as_default():
  od_graph_def = tf.GraphDef()
  with tf.gfile.GFile(PATH_TO_CKPT, 'rb') as fid:
    serialized_graph = fid.read()
    od_graph_def.ParseFromString(serialized_graph)
    tf.import_graph_def(od_graph_def, name='')


# ## Loading label map
# Label maps map indices to category names, so that when our convolution network predicts `5`, we know that this corresponds to `airplane`.  Here we use internal utility functions, but anything that returns a dictionary mapping integers to appropriate string labels would be fine

# In[ ]:


label_map = label_map_util.load_labelmap(PATH_TO_LABELS)
categories = label_map_util.convert_label_map_to_categories(label_map, max_num_classes=NUM_CLASSES, use_display_name=True)
category_index = label_map_util.create_category_index(categories)


# ## Helper code

# In[ ]:


def load_image_into_numpy_array(image):
  (im_width, im_height) = image.size
  return np.array(image.getdata()).reshape(
      (im_height, im_width, 3)).astype(np.uint8)


# # Detection

# In[ ]:


# For the sake of simplicity we will use only 2 images:
# image1.jpg
# image2.jpg
# If you want to test the code with your images, just add path to the images to the TEST_IMAGE_PATHS.
PATH_TO_TEST_IMAGES_DIR = 'test_images'
TEST_IMAGE_PATHS = [ os.path.join(PATH_TO_TEST_IMAGES_DIR, 'image{}.jpg'.format(i)) for i in range(1, 3) ]

# Size, in inches, of the output images.
IMAGE_SIZE = (12, 8)


# In[ ]:


#def run_inference_for_single_image(image, graph):
  


gpu_options = tf.GPUOptions(per_process_gpu_memory_fraction=0.7)
with detection_graph.as_default():
  with tf.Session(graph=detection_graph,config=tf.ConfigProto(gpu_options=gpu_options)) as sess:
	while True:
          turn=1
	  ret,image_np=cap.read()
	  # Expand dimensions since the model expects images to have shape: [1, None, None, 3]
	  image_np_expanded = np.expand_dims(image_np, axis=0)
          image_tensor = detection_graph.get_tensor_by_name('image_tensor:0')
          ##box
          boxes = detection_graph.get_tensor_by_name('detection_boxes:0')
          ####scores
          scores = detection_graph.get_tensor_by_name('detection_scores:0')
          classes = detection_graph.get_tensor_by_name('detection_classes:0')
          num_detections = detection_graph.get_tensor_by_name('num_detections:0')
	  # Actual detection.
	  (boxes, scores, classes, num_detections) = sess.run(
              [boxes, scores, classes, num_detections],
              feed_dict={image_tensor: image_np_expanded})
	  # Visualization of the results of a detection.
	  vis_util.visualize_boxes_and_labels_on_image_array(
	      image_np,
	      np.squeeze(boxes) ,
	      np.squeeze(classes) .astype(np.int32) ,
	      np.squeeze(scores) ,
	      category_index,
	      use_normalized_coordinates=True,
	      line_thickness=8)
          for i,b in enumerate(boxes[0]):
              if classes[0][i] >=1 and classes[0][i]<=500:
		if scores[0][i] > 0.7:
		  mid_x = (boxes[0][i][3]+boxes[0][i][1])/2
		  mid_y = (boxes[0][i][2]+boxes[0][i][0])/2
		  apx_distance = round((1-(boxes[0][i][3]-boxes[0][i][1]))**2,1)
		  cv2.putText(image_np,'{}'.format(apx_distance),(int(mid_x*800),int(mid_y*600)),cv2.FONT_HERSHEY_SIMPLEX,1,(255,255,255),2)
		  if apx_distance <= 0.9:
		     if mid_x >0.3 and mid_x <0.7:
			 cv2.putText(image_np,'WARNING!!',(int(mid_x*800)-50,int(mid_y*600)),cv2.FONT_HERSHEY_SIMPLEX,0.7,(0 ,0,255),2)
                         if mid_x>0.3 and mid_x<0.5:
                            turn = 3
                         elif mid_x>0.5 and mid_x<0.7:
                            turn = 2
                    
                  else:
                     turn=1
              pub.publish(turn) 
              #rate_1.sleep()




	  cv2.imshow('object',cv2.resize(image_np,(800,600)))
	  if cv2.waitKey(25) & 0xFF == ord('q'):
	     break
