#!/usr/bin/env python
 
import rospy
from laser_assembler.srv import AssembleScans
from sensor_msgs.msg import PointCloud

rospy.init_node("assemble_scans_to_cloud")
rospy.wait_for_service("assemble_scans")
assemble_scans = rospy.ServiceProxy('assemble_scans',AssembleScans)
pub = rospy.Publisher("/laser_pointcloud",PointCloud,queue_size=1)

r=rospy.Rate(1)

while(True):
	try:
		resp= assemble_scans(rospy.Time(0,0),rospy.get_rostime())
		pub.publish(resp.cloud)

	except rospy.ServiceException,e:
		print "Service call failed: %s"%e

	r.sleep()

