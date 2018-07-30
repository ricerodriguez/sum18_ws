#include "LineFollower.h"
#include <iostream>

LineFollower::LineFollower(ros::NodeHandle* nodehandle):nh_(*nodehandle) {
     ROS_INFO("Constructing the Line Follower class...");
     this->initializeSubscribers();
     this->initializePublishers();
}

void LineFollower::initializeSubscribers() {
     ROS_INFO("Initializing subscribers...");
     sub_left_ = nh_.subscribe("/test_drive_controller/sens_ir/left",100,&LineFollower::leftSubscriberCallback, this);
     sub_right_ = nh_.subscribe("/test_drive_controller/sens_ir/right",100,&LineFollower::rightSubscriberCallback, this);
}

void LineFollower::leftSubscriberCallback(const constIllumPtr &msg) {
     this->infraleft_ = msg->illuminance;
     this->navCenter();
}

void LineFollower::rightSubscriberCallback(const constIllumPtr &msg) {
     this->infraright_ = msg->illuminance;
     this->navCenter();
}

void LineFollower::navCenter() {
     if (this->infraleft_ && !this->infraright_) {
          // If left sensor detects but right sensor does not, set nav to go left
          dir_ = "left";
     } else if (!this->infraleft_ && this->infraright_) {
          // If right sensor detects but left sensor does not, set nav to go right
          dir_ = "right";
     } else if (this->infraleft_ && this->infraright_) {
          // If both sensors are detecting, stop
          dir_ = "stop";
     } else if (!this->infraleft_ && !this->infraright_) {
          // If neither sensor is detecting, keep going straight
          dir_ = "forward";
     }
}

void LineFollower::initializePublishers() {
     ROS_INFO("Initializing publishers...");
     pub_ = nh_.advertise<geometry_msgs::Twist>("/test_drive_controller/cmd_vel", 100);
     // Initialize the message
     geometry_msgs::Twist msg;
     msg.linear.x = 0;
     msg.linear.y = 0;
     msg.linear.z = 0;

     msg.angular.x = 0;
     msg.angular.y = 0;
     msg.angular.z = 0;

     ros::Rate rate(10);
     while(ros::ok()) {
          this->followTheLine();
          ros::spinOnce();
          rate.sleep();
     }
}

void LineFollower::followTheLine() {
     switch (dir_) {
          case "left":
               ROS_INFO("Going left!");
               msg.linear.x = -0.1;
               msg.angular.z = 0.1;
               break;
          case "right":
               ROS_INFO("Going right!");
               msg.linear.x = -0.1;
               msg.angular.z = -0.1;
               break;
          case "stop":
               ROS_INFO("Stop!");
               msg.linear.x = 0.0;
               msg.angular.z = 0.0;
               break;
          case "forward":
               ROS_INFO("Going straight!");
               msg.linear.x = -0.1;
               msg.angular.z = 0.0;
     }
}

int main(int argc, char** argv) {
     ros::init(argc, arv, "line_follower");
     ros::NodeHandle nh;

     ROS_INFO("Instantiating an object of type LineFollower...");
     LineFollower lemming(&nh);
     ROS_INFO("Letting the callbacks do the rest of the work...");
     ros::spin();
     return 0;
}
