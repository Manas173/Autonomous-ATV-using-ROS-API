#!/usr/bin/env python

import rospy
from geometry_msgs.msg import PointStamped
import tf
import time
from tf import TransformListener
x=[]
y=[]
z=[]
def callBack(msg):
    global x
    global y
    global z
    x.appned(msg.points[0].x)
    y.append(msg.points[0].y)
    z.append(msg.points[0].z)

def transformPoint(listener):
    laser_point=geometry_msgs.PointStamped
    laser_point.header.frame_id="laser_scan"
    laser_point.header.stamp=rospy.Time()
    for i in range(0,len(x)):
      laser_point.point.x=x[i]
      laser_point.point.y=y[i]
      laser_point.point.z=z[i]
    try:
       base_point=geometry_msgs.PointStamped
       listener.transformPoint("laser_frame",laser_point,base_point)
       
    except(ex):
       print "ok"

def mainprog():
    rospy.init_node("robot_tf_listener",anonymous=True)
    listener=tf.TransformListener(rospy.Duration(10))
    timer=time.createTimer(rospy.Duration(1.0),boost.bind(transformPoint,boost.ref(listener)))
    sub=rospy.Subscriber("cloud",1000,callBack)
    print "ok1"
    rospy.spin()

if __name__=='__main__':
    mainprog()
