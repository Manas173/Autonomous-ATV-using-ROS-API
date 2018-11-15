#!/usr/bin/env python

import rospy
from sensor_msgs.msg import PointCloud2 as pc2
string
class Laser2PC1():
    def __init__(self):
   
        self.pcPub = rospy.Publisher("/cloud_new",pc2,queue_size=1)
        self.laserSub = rospy.Subscriber("/cloud",pc2,self.laserCallback)

    def laserCallback(self,data1):
        global string
        data1.data = string+data1.data
        string=data1.data
        self.pcPub.publish (data1.data)

if __name__ == '__main__':
    rospy.init_node("laser2PointCloud")
    l2pc = Laser2PC1()
    rospy.spin()
 
