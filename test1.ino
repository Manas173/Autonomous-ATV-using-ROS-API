#include <stdio.h>
#include <ros.h>
#include <stdlib.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <pub/Num.h>
#include <Servo.h>

Servo myservo;
Servo myservo2;
int pos = 0;
int flag=0;
int upflag=0;
int pos2=0;
ros::NodeHandle n;
pub::Num var;
ros::Publisher chat("chatter",&var);
#define trigPin 13
#define echoPin 12
float theta=-3.14159;
float phi=3.14159/3.0;
void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    n.initNode();
    myservo.attach(10);
    n.advertise(chat);
    myservo2.attach(5);
    myservo2.write(0);
    myservo.write(0);
}

void loop()
{
    long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance >= 200 || distance <= 0)
  {
    var.r=0;
    var.theta=theta;
    var.phi=phi;
    }
  else {
    int16_t sum=distance;
    var.r=sum;
    var.theta=theta;
    var.phi=phi;
  }             
    if(pos==180)
      {
       flag=1;
       upflag=1;
      }
    else if(pos==0)
       {
        flag=0;
        upflag=1;
       }
    if(upflag==1)
       {
        pos2=pos2+2;
        myservo2.write(pos2);
        upflag=0;
       }
    if(flag==1 && upflag==0)
      pos=pos-1;
    else if(flag==0 && upflag==0)
      pos=pos+1;
    
    theta=(((float)(pos)*3.14159)/180.0);
    phi=(((float)(pos2)*3.14159)/180.0);
    myservo.write(pos);
    // tell servo to go to position in variable 'pos'
    chat.publish(&var);
    delay(100);
    n.spinOnce();
}

