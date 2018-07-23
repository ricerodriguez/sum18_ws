#include "LineFollower.h"
#include <iostream>

LineFollower::LineFollower(ros::NodeHandle* nodehandle):nh_(*nodehandle) {
     ROS_INFO("Constructing the Line Follower class...");
     this->initializeSubscribers();
     this->initializePublishers();
}

void LineFollower::initializeSubscribers() {
}
