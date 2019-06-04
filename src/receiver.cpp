#include "ros/ros.h"
#include <std_msgs/Header.h>
#include<vector>
#include<iostream>
#include<string>

using namespace std;


vector<ros::Time> recv_time;
vector<ros::Time> tran_time;

int spin_cnt = 0;
int prev_seq = 0;
int loss_cnt = 0;

void chatterCallback(const std_msgs::Header& msg)
{
  ROS_INFO("count:%d , time:%d", msg.seq, msg.stamp.sec);
  tran_time.push_back(msg.stamp);
  recv_time.push_back(ros::Time::now());
  spin_cnt += 1;
  if((msg.seq != prev_seq+1) && (prev_seq != 0))
    loss_cnt ++;
  prev_seq = msg.seq;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "receiver");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("input", 1000, chatterCallback);
  
  while(spin_cnt <1000){
    
    ros::spinOnce();
  }
  double latency_acc = 0;
  for(int i = 0; i < tran_time.size(); i++){
  
    latency_acc +=  (recv_time[i].sec -  tran_time[i].sec)  + (recv_time[i].nsec -  tran_time[i].nsec) * 1e-9 ; 
  }
  double latency_avg = latency_acc / spin_cnt ; 
  
  cout.precision(10);
  cout << "Total number of message: " << spin_cnt << endl;
  cout << "Average latency of message: " << latency_avg << endl;
  cout <<  "Total number of loss: " << loss_cnt << endl;
  return 0;
}
