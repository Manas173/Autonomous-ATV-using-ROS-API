import rospy
import tf
import geometry_msgs.msg
t = tf.Transformer(True, rospy.Duration(10.0))
m = geometry_msgs.msg.TransformStamped()
m.header.frame_id = 'Laser_scan'
m.child_frame_id = 'world'
m.transform.translation.x = 2.71828183
m.transform.rotation.w = 1.0
t.setTransform(m)

t.lookupTransform('THISFRAME', 'CHILD', rospy.Time(0))



#####################################################
#!/usr/bin/env python
import rospy
import tf
from std_msgs.msg import String
import geometry_msgs.msg

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    
def listener():

    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("chatter", String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
