#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>
#include <sensor_msgs/PointCloud2.h>
#include <std_msgs/String.h>
#include <vector>
using std::vector;
int i=0;
float x;
float y;
float z;
//geometry_msgs::PointStamped msg;
geometry_msgs::PointStamped base_point;
//ros::NodeHandle n;
//ros::Publisher pu=n.advertise<geometry_msgs::PointStamped>("base",1000);
void callBack(const sensor_msgs::PointCloud& msg)
{  
   x=msg.points[i].x;
   y=msg.points[i].y;
   z=msg.points[i].z;
   i++;
}


void transformPoint( tf::TransformListener& listener);

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_tf_listener123");
  ros::NodeHandle n;
  tf::TransformListener listener(ros::Duration(10));
  //ROS_INFO("This is printed");
  //we'll transform a point once every second
  ros::Timer timer = n.createTimer(ros::Duration(1.0), boost::bind(&transformPoint, boost::ref(listener)));
  ros::Subscriber sub = n.subscribe("cloud",10,callBack);
  ros::Publisher pu=n.advertise<geometry_msgs::PointStamped>("base",1000);
  //ros::Publisher pu=n.advertise<geometry_msgs::PointStamped>("base",10);
  ros::Rate loopRate(10);
   //pu.publish(base_point);
   while(ros::ok())
   {
     pu.publish(base_point);
     ros::spinOnce();
     loopRate.sleep();
   }
  ros::spin();

}

void transformPoint( tf::TransformListener& listener){
  //we'll create a point in the base_laser frame that we'd like to transform to the base_link frame
  geometry_msgs::PointStamped laser_point;
  laser_point.header.frame_id = "laser_frame";

  //we'll just use the most recent transform available for our simple example
  laser_point.header.stamp = ros::Time();

  //just an arbitrary point in space
  laser_point.point.x =x;
  laser_point.point.y =y;
  laser_point.point.z =z;

  try{
    listener.transformPoint("world", laser_point, base_point);
    ROS_INFO("base_laser: (%.2f, %.2f. %.2f) -----> laser_frame: (%.2f, %.2f, %.2f) at time %.2f",
        laser_point.point.x, laser_point.point.y, laser_point.point.z,
        base_point.point.x, base_point.point.y, base_point.point.z, base_point.header.stamp.toSec());
  }
  catch(tf::TransformException& ex){
    ROS_ERROR("Received an exception trying to transform a point from \"world\" to \"laser_frame\": %s", ex.what());
  }
}

