#include <ros/ros.h>
#include <iostream>
#include "Timid.h"

TimidClass::TimidClass(ros::NodeHandle* nodehandle):nh_(*nodehandle) {
     ROS_INFO_STREAM("Constructing the Timid Class..." << std::endl);
     this->initializeSubscribers();
     this->initializePublishers();
     // this->initializeActionServers();
}

// void TimidClass::initializeActionClient() : ac_("turn_and_stop", true) {
//      ROS_INFO("Waiting for action server to start...");
//      ac.waitForServer();
//      ROS_INFO("Action server started! Sending goal...");
// }
//
//
// void TimidClass::initializeActionServers(std::string srv_name) : as_(nh_, srv_name, boost::bind(&TimidClass::actCallback, this, _1), false), srv_(srv_name) {
//      ROS_INFO_STREAM("Initializing action server..." << std::endl);
//      as_.start();
// }
//
// void TimidClass::actCallback(const constGoalPtr &goal) {
//      ros::Rate rate(1);
//      bool success = true;
//
//      goal_.range_data = this->range_;
//      if (goal_.range_data < 0.95 && goal_.range_data >= 0.03) {
//           result_.ang_z = 0.1;
//           result_.lin_x = 0.0;
//      }
//
//      result_.lin_x = 0.1;
// }

void TimidClass::initializeSubscribers() {
     ROS_INFO_STREAM("Initializing subscribers..." << std::endl);
     sub_sens_ = nh_.subscribe("/test_drive_controller/sens_ir/fwd", 100, &TimidClass::sensSubscriberCallback, this);
}

void TimidClass::sensSubscriberCallback(const constLaserScanPtr &msg) {
     // this->range_ = msg->range;
     this->vector_ = msg->ranges;
     this->range_ = this->vector_.back();
     // ROS_INFO_STREAM("Callback initiated. Received value: " << this->range_ << std::endl);
}

void TimidClass::initializePublishers() {
     ROS_INFO_STREAM("Initializing publishers..." << std::endl);
     pub_ = nh_.advertise<geometry_msgs::Twist>("/test_drive_controller/cmd_vel", 100);
     // Initialize the message
     geometry_msgs::Twist msg;

     msg.linear.x = 0.0;
     msg.linear.y = 0.0;
     msg.linear.z = 0.0;

     msg.angular.x = 0.0;
     msg.angular.y = 0.0;
     msg.angular.z = 0.0;

     ros::Rate rate(10);
     while(ros::ok()) {
          this->runAway();
          ros::spinOnce();
          rate.sleep();
     }
}

void TimidClass::runAway() {
     geometry_msgs::Twist msg;
     if (this->range_ > 0.95 || this->range_ < 0.03) {
          ROS_INFO("Out of range, going straight.");
          msg.linear.x = -0.1;
          msg.linear.y = 0.0;
          msg.linear.z = 0.0;
          msg.angular.x = 0.0;
          msg.angular.z = 0.0;
          msg.angular.y = 0.0;
     } else {
          ROS_INFO("AAAAH! Something is %f meters ahead!! Scanning for clear path...",this->range_);
          msg.angular.z = 0.1;
          msg.linear.x = 0.0;
          msg.linear.y = 0.0;
          msg.linear.z = 0.0;
     }
     pub_.publish(msg);
}

int main (int argc, char** argv) {
     ros::init(argc, argv, "timid_robot");
     ros::NodeHandle nh;

     ROS_INFO_STREAM("Instantiating an object of type TimidClass..." << std::endl);
     TimidClass timothy(&nh);
     ROS_INFO_STREAM("Letting the callbacks do the rest of the work...");
     ros::spin();
     return 0;
}
