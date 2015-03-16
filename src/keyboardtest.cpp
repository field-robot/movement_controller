#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"


#include <sstream>

int value = 100;

int main(int argc, char **argv)
{

  ros::init(argc, argv, "error_handling");

  ros::NodeHandle n;

 
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("keyboard", 1000);

  ros::Rate loop_rate(10);

  
  while (ros::ok())
  {
    std_msgs::Int8 msg;
    msg.data = value;


    ROS_INFO("%i", msg.data);

  
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    
  }


  return 0;
}
