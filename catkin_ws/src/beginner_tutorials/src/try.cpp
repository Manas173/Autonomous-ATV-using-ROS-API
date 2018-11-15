#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
int16_t *dat,i=0,max = 10000,j=0;
void chatterCallback(const std_msgs::Int16::ConstPtr& msg)
{
  if(i<180)
{
  dat[i] = msg->data;
  ROS_INFO("I heard: [%d], [%d]", dat[i],i);
  i=i+1;
  //dat = (int16_t*)realloc(dat,i*(sizeof(int16_t)));
}
 if(i>=180)
 {
   for(j=0;j<180;j++)
   {
     ROS_INFO("[%d],[%d]",dat[j],j);
   }
 }

}

int main(int argc, char **argv)
{
  
  //dat = (int16_t*)malloc(sizeof(int16_t));
  dat = new int16_t[max];
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  ros::spin();
  return 0;
}
