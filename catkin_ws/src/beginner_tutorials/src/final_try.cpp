#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
float y=0.0,z=0.0;
float dat;
visualization_msgs::Marker sphere_list;
geometry_msgs::Point p;
void chatterCallback(const std_msgs::Float32::ConstPtr& msg)
{ 
  dat = msg->data;
  ROS_INFO("[%f]",dat);
  ros::Time scan_time1 = ros::Time::now();
  
  p.x = dat;
  p.y = y;
  p.z = z;
  y=y+1.0;
  if(y>10)
  {
    z=z+1.0;
    y=0.0;
  }
  if(z>10.0)
  {
    z=0.0;
  }
  sphere_list.points.push_back(p);
  
} 
int main( int argc, char** argv )
{
  ros::init(argc, argv, "spheres");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("ball_trajectory", 10);

  ros::Rate r(30);

  float f = 0.0;
  while (ros::ok())
  {

    visualization_msgs::Marker sphere_list;
    sphere_list.header.frame_id= "/my_frame";
    sphere_list.header.stamp= ros::Time::now();
    sphere_list.ns= "spheres";
    sphere_list.action= visualization_msgs::Marker::ADD;
    sphere_list.pose.orientation.w= 1.0;

    sphere_list.id = 0;

    sphere_list.type = visualization_msgs::Marker::SPHERE_LIST;


    // POINTS markers use x and y scale for width/height respectively
    sphere_list.scale.x = 0.1;
    sphere_list.scale.y = 0.1;
    sphere_list.scale.z = 0.1;

    // Points are green
    sphere_list.color.r = 1.0f;
    sphere_list.color.a = 1.0;


    // Create the vertices for the points and lines
    /*for (uint32_t i = 0; i < 25; ++i)
    {
      float y = sin(f + i / 100.0f * 2 * M_PI);
      float z = cos(f + i / 100.0f * 2 * M_PI);

      
      p.x = (int32_t)i*0.2;
      p.y = y;
      p.z = z;

      sphere_list.points.push_back(p);

    }*/
    //sphere_list.points.push_back(p);
    marker_pub.publish(sphere_list);

    r.sleep();
    ros::spinOnce();
    f += 0.04;
  }
}
