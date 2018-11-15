#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Float32.h>
void chatterCallback(const std_msgs::Float32::ConstPtr& msg)
{
  ROS_INFO("I heard: [%f]", msg->data);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "my_tf_broadcaster");
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("chatter1", 1000, chatterCallback);
  ros::spin();
  return 0;
}
