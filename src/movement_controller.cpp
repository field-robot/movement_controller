#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <sstream>


int main(int argc, char **argv)
{

  ros::init(argc, argv, "movement_controller");


  ros::NodeHandle n;


  ros::Publisher chatter_speed_LF = n.advertise<std_msgs::Int8>("speed_LF", 1000);
  ros::Publisher chatter_speed_LB = n.advertise<std_msgs::Int8>("speed_LB", 1000);
  ros::Publisher chatter_speed_RF = n.advertise<std_msgs::Int8>("speed_RF", 1000);
  ros::Publisher chatter_speed_RB = n.advertise<std_msgs::Int8>("speed_RB", 1000);

  ros::Rate loop_rate(10);


  int speed_LF = 0;
  int speed_LB = 50;
  int speed_RF = 100;
  int speed_RB = 150;

  while (ros::ok())
  {

    std_msgs::Int8 msg_speed_LF;
    std_msgs::Int8 msg_speed_LB;
    std_msgs::Int8 msg_speed_RF;
    std_msgs::Int8 msg_speed_RB;

    msg_speed_LF.data = speed_LF;
    msg_speed_LB.data = speed_LB;
    msg_speed_RF.data = speed_RF;
    msg_speed_RB.data = speed_RB;

    //ROS_INFO("%i", msg.data);

    chatter_speed_LF.publish(msg_speed_LF);
    chatter_speed_LB.publish(msg_speed_LB);
    chatter_speed_RF.publish(msg_speed_RF);
    chatter_speed_RB.publish(msg_speed_RB);

    ros::spinOnce();

    loop_rate.sleep();
    ++speed_LF;
    ++speed_LB;
    ++speed_RF;
    ++speed_RB;
  }


  return 0;
}
