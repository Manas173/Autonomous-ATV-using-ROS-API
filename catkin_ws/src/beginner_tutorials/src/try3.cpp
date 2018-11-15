#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Point32.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Vector3.h>




float *Buffer;
int16_t j=0,max=10000;
float dat;
int16_t num_readings=180;

void chatterCallback(const std_msgs::Float32::ConstPtr& msg)
{ 
  dat = msg->data;
  ROS_INFO("[%f]",dat);
  ros::Time scan_time1 = ros::Time::now();
  
  
   if(j<180)
  {
   Buffer[j]=dat;
   //ROS_INFO("[%f],[%d]",Buffer[j],j);
   j=j+1;
   //Buffer = (int16_t *)realloc(Buffer,j);
   if(j>=180)
  {
   j=0;
  }

   }
  
} 

int main(int argc, char** argv)
{ //Buffer = (int16_t *)malloc(sizeof(int16_t));
  Buffer = new float[max];
  ros::init(argc, argv, "laser_scan_publisher");

  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan", 50);
  double laser_frequency = 0.011112;
  double ranges[num_readings];
  double intensities[num_readings];

  int count = 0;
  ros::Rate r(1.0);

  while(ros::ok()){
    //generate some fake data for our laser scan
    ros::Time scan_time = ros::Time::now();


visualization_msgs::Marker sphere_list;
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
    for (uint32_t i = 0; i < 25; ++i)
    {
      float y = sin(f + i / 100.0f * 2 * M_PI);
      float z = cos(f + i / 100.0f * 2 * M_PI);
      geometry_msgs::Point p;
      p.x = (int32_t)i*0.2;
      p.y = y;
      p.z = z;
      sphere_list.points.push_back(p);
    }
    marker_pub.publish(sphere_list);
    f += 0.04;
    //populate the LaserScan message
    sensor_msgs::LaserScan scan;
    scan.header.stamp = scan_time;
    scan.header.frame_id = "laser_frame";
    scan.angle_min = -1.57;
    scan.angle_max = 1.57;
    scan.angle_increment = 3.14 / num_readings;
    scan.time_increment = (1 / laser_frequency) / (num_readings);
    scan.range_min = 0.0;
    scan.range_max = 10.0;

    scan.ranges.resize(num_readings);
    scan.intensities.resize(num_readings);
    for(unsigned int i = 0; i < num_readings; ++i){
      scan.ranges[i] = Buffer[i];
      
    }

    scan_pub.publish(scan);
    ++count;
    r.sleep();
    ros::spinOnce();
    
  }

  //ros::spin();
return 0;
}






int main( int argc, char** argv )
{
  //ros::init(argc, argv, "spheres");
  //ros::NodeHandle n;
  //ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("ball_trajectory", 10);

  //ros::Rate r(30);

  float f = 0.0;
  while (ros::ok())
  {

    visualization_msgs::Marker sphere_list;
    //sphere_list.header.frame_id= "/my_frame";
    //sphere_list.header.stamp= ros::Time::now();
    //sphere_list.ns= "spheres";
    //sphere_list.action= visualization_msgs::Marker::ADD;
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
    for (uint32_t i = 0; i < 25; ++i)
    {
      float y = sin(f + i / 100.0f * 2 * M_PI);
      float z = cos(f + i / 100.0f * 2 * M_PI);

      geometry_msgs::Point p;
      p.x = (int32_t)i*0.2;
      p.y = y;
      p.z = z;

      sphere_list.points.push_back(p);

    }
    marker_pub.publish(sphere_list);

    //r.sleep();

    f += 0.04;
  }
}
