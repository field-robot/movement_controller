#include "ros/ros.h"
#include "std_msgs/UInt8.h"
#include <sstream>
#include "std_msgs/String.h"


/*///////NEW CODE


void chatterCallback(const std_msgs::Int8::ConstPtr& msg)
{
}
/*
{
  ROS_INFO("I heard: [%i]", msg->data);//.c_str());
}
/
std_msgs::Int8 msg;


/////////END NEW CODE*/







int main(int argc, char **argv)
{







  //ROS package name
  ros::init(argc, argv, "movement_controller");
  ros::NodeHandle n;

  //ROS set publish variables equal message variables
  ros::Publisher chatter_speed_LF = n.advertise<std_msgs::UInt8>("speed_LF", 1000);
  ros::Publisher chatter_speed_LB = n.advertise<std_msgs::UInt8>("speed_LB", 1000);
  ros::Publisher chatter_speed_RF = n.advertise<std_msgs::UInt8>("speed_RF", 1000);
  ros::Publisher chatter_speed_RB = n.advertise<std_msgs::UInt8>("speed_RB", 1000);

  //ROS ??
  ros::Rate loop_rate(10);

  //Programm Declare variables
  int speed_LF = 0; //For publishing
  int speed_LB = 0; //For publishing
  int speed_RF = 0; //For publishing
  int speed_RB = 0; //For publishing

  float offset_FW = 100;   //For subscribing current motor offset related to the row
  float angle_FW =  0; //For subscribing current motor angle related to the row

  float formula_a = 2000; 	//(1/a)X^b
  float formula_b = 2;		//(1/a)X^b
  float angle_setpoint = 0; 	//desired angle value on specific robot location
  float angle_error = 0;    	//diference between angle_FW and angle_setpoint
  float motor_amplification = 10; //determines the change in RPM factor of the motor
  float correction_sign = 1;      //correction sign for forward and backward driving (1 or -1)

  //Programm loop
  while (ros::ok())
  {
    //ROS declare message variables
    std_msgs::UInt8 msg_speed_LF;
    std_msgs::UInt8 msg_speed_LB;
    std_msgs::UInt8 msg_speed_RF;
    std_msgs::UInt8 msg_speed_RB;

    //ROS Set messages variables equal to variables
    msg_speed_LF.data = speed_LF;
    msg_speed_LB.data = speed_LB;
    msg_speed_RF.data = speed_RF;
    msg_speed_RB.data = speed_RB;

    //ROS_INFO("%i", msg.data);  //Display variable when running package
      

    //ROS publish variables
    chatter_speed_LF.publish(msg_speed_LF);
    chatter_speed_LB.publish(msg_speed_LB);
    chatter_speed_RF.publish(msg_speed_RF);
    chatter_speed_RB.publish(msg_speed_RB);

    //ROS run code to publish on topic
    ros::spinOnce();

    //PROGRAMM CODE
    loop_rate.sleep();
    
    //Forward driving
    if (offset_FW < 0) {
      correction_sign = -1;
    } else {
      correction_sign = 1;
    }

    angle_setpoint = ((1.0/formula_a)*(offset_FW*offset_FW)*-1.0*correction_sign);
    angle_error = angle_setpoint - angle_FW;

    speed_RF = angle_setpoint;
    speed_LF = angle_error;
    speed_LB = formula_a;

    //Motor control
    if (angle_error>0) {
      speed_LF = 255;
      speed_LB = 255;
      speed_RF = 255-(angle_error*motor_amplification);
      speed_RB = 255-(angle_error*motor_amplification);
    }

    if (angle_error<0) {
      speed_LF = 255-(angle_error*-1.0*motor_amplification);
      speed_LB = 255-(angle_error*-1.0*motor_amplification);
      speed_RF = 255;
      speed_RB = 255;
    }   

/* NEW CODE


ros::init(argc, argv, "listener");




  ros::Subscriber sub = n.subscribe("speed_LF", 1000, chatterCallback);

  ROS_INFO("I heard: [%i]", msg.data);//.c_str());
  ros::spinOnce();



*/////////END NEW CODE
      
  }







  return 0;
}
