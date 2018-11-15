#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>
#include <tf/transform_listener.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

ros::Publisher pub;
tf::TransformListener *tf_listener; 

void callback(const PointCloud::ConstPtr& in)
{
  tf_listener->waitForTransform("/laser_frame", "/world", ros::Time(0), ros::Duration(10.0));
  PointCloud out;
  pcl_ros::transformPointCloud("/laser_scan", *in, out, *tf_listener);
  pub.publish(out);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "kinect_transform_node");
  ros::NodeHandle nh1;
  pub = nh1.advertise<PointCloud> ("transformed_points", 1);
  
  tf_listener    = new tf::TransformListener();

  ros::NodeHandle nh2;
  ros::Subscriber sub = nh2.subscribe<PointCloud>("/cloud", 1, callback);

  ros::spin();
}

