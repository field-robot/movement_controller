#include "ros/ros.h"
#include "std_msgs/Int8.h"


#include <sstream>


int main(int argc, char **argv)
{

  ros::init(argc, argv, "movement_controller");


  ros::NodeHandle n;


  ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("speed_LF", 1000);

  ros::Rate loop_rate(10);


  int count = 0;
  while (ros::ok())
  {

    std_msgs::Int8 msg;

    msg.data = count;

    ROS_INFO("%i", msg.data);


    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
