#!/usr/bin/env python
 
import rospy
from laser_assembler.srv import AssembleScans
from sensor_msgs.msg import PointCloud
from std_msgs.msg import Float32
rospy.init_node("assemble_scans_to_cloud")
rospy.wait_for_service("assemble_scans")
assemble_scans = rospy.ServiceProxy('assemble_scans',AssembleScans)
pub = rospy.Publisher("/laser_pointcloud",PointCloud,queue_size=1)

pt=0
def callback(msg):
      global pt
      if msg.data==1 :
           pt=1

rospy.Subscriber("chatter2", Float32, callback)

r=rospy.Rate(1)

while(True):
	try:
		resp= assemble_scans(rospy.Time(0,0),rospy.get_rostime())
                x = resp.cloud
                pub.publish(x)
                if pt==1 :
                   del x[:]
                   pt=0
 
		#resp.cloud.points = x
		print "Got cloud with %u points" % len(x.points)
		
		

	except rospy.ServiceException,e:
		print "Service call failed: %s"%e

	r.sleep()

