#include"ros/ros.h"
#include"sensor_msgs/NavSatFix.h"
#include<math.h>
#include<std_msgs/Float64.h>
#include<std_msgs/Float32MultiArray.h>
#include<std_msgs/Int8.h>

float r=6378,encodis=0,PI=3.1414;
float slat;
float slon;
float dlat,dlon,x1,x2,x3,x4,d,a,c,n,m;
float encoder;
float distance;
int8_t output;
float angle;
float angle_current;
int count=1;
int turn=0;
int flag_lon=0,flag_lat=0;
float lon[200],lat[200];
int num=0;

void chattercallback(const sensor_msgs::NavSatFix::ConstPtr& msg)
{  
	x1=slat*PI/180;
	x2=dlat*PI/180;
	x3=(dlat-slat)*PI/180;
	x4=(dlon-slon)*PI/180;	
	a=(sin(x3/2)*sin(x3/2)) + (cos(x1)*(cos(x2)*sin(x4/2)*sin(x4/2)));
	c=2*atan2(sqrt(a),sqrt(1-a));
	d = r*c*1000;
        m=sin(x4)*cos(x2);
        n=(cos(x1)*sin(x2))-(sin(x1)*cos(x2)*cos(x4));
        angle=(atan2(m,n));
        angle = (180/PI)*angle;
        angle = (int)(angle+360)%360;


	//ros::param::get("/routing_machine/destination/latitude", global_name);
    //ROS_INFO("destination is:[%f]", global_name);
}

void encodercallback(const std_msgs::Float64::ConstPtr& msg1)
{
  encoder = msg1->data;
  distance = ((37.68/320)/100)*encoder;
  distance=distance-turn;
  if (((angle_current)-angle)>10)
  {
   output = 2;    //left
  }
  else if (((angle_current)-angle)<-10)
  {
   output = 3;    //right
  }
  else
  {
   if (distance>d && count<num)
   {
      output =5;   //stop
      slon=dlon;
      slat=dlat;
      count++;
      dlon=lon[count];
      dlat=lat[count];
      turn=turn+distance;
      ROS_INFO("******************** CHANGE OF WAYPOINT **********************")
      ROS_INFO("the start has been changed to :");
      ROS_INFO("start latitude: [%f]",slat);
      ROS_INFO("start longitude: [%f]",slon);
      ROS_INFO("the destination has been changed to :");
      ROS_INFO("destination latitude: [%f]",dlat);
      ROS_INFO("destination longitude: [%f]",dlon);
   }
  if(distance<=d)
   {
      output =1;  //forward 
   }
   } 
}

void compass(const std_msgs::Float64::ConstPtr& msg1)
{
  angle_current = msg1->data;
  angle_current=int(angle_current)%360; 
  ROS_INFO("start latitude: [%f]",slat);
  ROS_INFO("start longitude: [%f]",slon);
  ROS_INFO("destination latitude: [%f]",dlat);
  ROS_INFO("destination longitude: [%f]",dlon);
  ROS_INFO("current angle: [%f]", angle_current);
  ROS_INFO("distance of encoder is:[%f]", distance);
  ROS_INFO("distance to destination:[%f]", d);
  ROS_INFO("angle is:[%f]", angle);
  ROS_INFO("output is [%d]", output);
  
}

void latitudecallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
if(flag_lat==0)
{
int i = 0;
	// print all the remaining numbers
	for(std::vector<float>::const_iterator it = msg->data.begin(); it != msg->data.end(); ++it)
	{
		lat[i] = *it;
		i++;
}
slat=lat[0];
dlat=lat[1];
ROS_INFO("slat [%f]", slat);
  ROS_INFO("dlat [%f]",dlat);
flag_lat=1;
}
}
void longitudecallback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
if(flag_lon==0)
     { 
int i = 0;
	// print all the remaining numbers
	for(std::vector<float>::const_iterator it = msg->data.begin(); it != msg->data.end(); ++it)
	{
		lon[i] = *it;
		i++;
num++;
}
slon=lon[0];
dlon=lon[1];
ROS_INFO("slon [%f]", slon);
ROS_INFO("dlon [%f]", dlon);
flag_lon=1;
}
}


int main(int argc, char **argv)
{
	ros::init(argc,argv, "example1_c");
	ros::NodeHandle n;
 
        ros::Subscriber sub3 = n.subscribe("latitude", 1000, latitudecallback);
        ros::Subscriber sub4 = n.subscribe("longitude", 1000, longitudecallback);  
	    ros::Subscriber sub = n.subscribe("/mavros/global_position/global", 1000, chattercallback);      
        ros::Subscriber sub2 = n.subscribe("/mavros/global_position/compass_hdg", 1000, compass);
        ros::Subscriber sub1 = n.subscribe("/my_topic", 1000, encodercallback);
        ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("chatter", 1000);
        ros::Rate loop_rate(10);
	
        while (ros::ok())
        {
         std_msgs::Int8 msg;
         msg.data = output;
         chatter_pub.publish(msg);
         
         ros::spinOnce();
         loop_rate.sleep();
         }
         ros::spin();
	return 0;
}

