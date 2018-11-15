#include <ros/ros.h>
#include <std_msgs/String.h>
#include <laser_geometry/laser_geometry.h>
#include <tf/transform_listener.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/LaserScan.h>

laser_geometry::LaserProjection projector_b;

sensor_msgs::PointCloud cloud;

void laserCallback (const sensor_msgs::LaserScan::ConstPtr& scan_in)
{    tf::TransformListener listener_a;
     if(!listener_a.waitForTransform(
        scan_in->header.frame_id,
        "laser_frame",
        scan_in->header.stamp + ros::Duration().fromSec(scan_in->ranges.size()*scan_in->time_increment),
        ros::Duration(1.0))){
     ROS_INFO("################################################################");
     return;
  }

  //sensor_msgs::PointCloud cloud;
  projector_b.transformLaserScanToPointCloud("laser_frame",*scan_in,
          cloud,listener_a);

  // Do something with cloud.
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listenening");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("scan", 1000, laserCallback);
  ros::Publisher chatter_pub = n.advertise<sensor_msgs::PointCloud>("cloud", 1000);
  ros::Rate loop_rate(10.0);

   while (ros::ok())
  {
    chatter_pub.publish(cloud);
    ros::spinOnce();
    loop_rate.sleep();  
  }
  
  

  return 0;
}
