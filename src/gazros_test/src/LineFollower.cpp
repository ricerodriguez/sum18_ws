#include "LineFollower.h"
#include <iostream>

LineFollower::LineFollower(ros::NodeHandle* nodehandle):nh_(*nodehandle) {
     ROS_INFO("Constructing the Line Follower class...");
     this->initializeSubscribers();
     this->initializePublishers();
}

void LineFollower::initializeSubscribers() {
     ROS_INFO("Initializing subscribers...");
     sub_left_ = nh_.subscribe("/sens_ir/left",100,&LineFollower::leftSubscriberCallback, this);
     sub_right_ = nh_.subscribe("/sens_ir/right",100,&LineFollower::rightSubscriberCallback, this);
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
          dir_ = LEFT;
     } else if (!this->infraleft_ && this->infraright_) {
          // If right sensor detects but left sensor does not, set nav to go right
          dir_ = RIGHT;
     } else if (this->infraleft_ && this->infraright_) {
          // If both sensors are detecting, stop
          dir_ = STOP;
     } else if (!this->infraleft_ && !this->infraright_) {
          // If neither sensor is detecting, keep going straight
          dir_ = FWD;
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
     geometry_msgs::Twist msg;
     switch (dir_) {
          case LEFT:
               ROS_INFO("Going left!");
               msg.linear.x = -0.1;
               msg.angular.z = 0.2;
               break;
          case RIGHT:
               ROS_INFO("Going right!");
               msg.linear.x = -0.1;
               msg.angular.z = -0.2;
               break;
          case STOP:
               ROS_INFO("Stop!");
               msg.linear.x = 0.0;
               msg.angular.z = 0.0;
               break;
          case FWD:
               ROS_INFO("Going straight!");
               msg.linear.x = -0.1;
               msg.angular.z = 0.0;
     }
     pub_.publish(msg);
}

int main(int argc, char** argv) {
     ros::init(argc, argv, "line_follower");
     ros::NodeHandle nh;

     ROS_INFO("Instantiating an object of type LineFollower...");
     LineFollower lemming(&nh);
     ROS_INFO("Letting the callbacks do the rest of the work...");
     ros::spin();
     return 0;
}
