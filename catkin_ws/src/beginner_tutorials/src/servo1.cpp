#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Float32.h>
#include <tf/transform_broadcaster.h>
float angle=0;
float angle1 = 0;
void chatterCallback(const std_msgs::Float32::ConstPtr& msg)
{
  ROS_INFO("I heard: [%f]", msg->data);
  angle=msg->data;
  angle = 0.044445*angle;
  if(angle1<-3.142)
     angle1=0;
  else
     angle1=angle1-(0.0174532925);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "my_tf_broadcaster");
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("chatter1", 1000, chatterCallback);
  
  tf::TransformBroadcaster br1;
  tf::Transform transform1;
  tf::Quaternion q;
  ros::Rate rate(10.0);
  while (node.ok()){
    q.setRPY(0.0,angle1,0.0);
    transform1.setOrigin( tf::Vector3(0.0, 0.0, 0.0) );
    //transform1.setRotation( tf::Quaternion(1.57, 0, 0, 1) );
    transform1.setRotation(q);
    
    br1.sendTransform(tf::StampedTransform(transform1, ros::Time::now(), "world", "laser_frame"));
    rate.sleep();
    ros::spinOnce();
  }
  //ros::spin();
  return 0;
}
