#include "ros/ros.h"
#include <std_msgs/Header.h>


#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "transmitter");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::Header>("input", 1000);

  ros::Rate loop_rate(50);

  int count = 0;
  while (ros::ok())
  {
    std_msgs::Header msg;
    msg.seq = count;
    msg.stamp = ros::Time::now();
    msg.frame_id = "transmiiter";

   // ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}