#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Range.h>

void leftCallback (const sensor_msgs::Range::ConstPtr &msg) {
     // ROS_INFO_STREAM("Left Infrared Seq: " << msg->header.seq << std::endl);
     // ROS_INFO_STREAM("Left Infrared Range: " << msg->range << std::endl);
     if (msg->range > 0.00640) {
          ROS_INFO_STREAM("Something to the left!" << std::endl);
     } else {
          ROS_INFO_STREAM("Nothing to the left!" << std::endl);
     }
}

void rightCallback (const sensor_msgs::Range::ConstPtr &msg) {
     // ROS_INFO_STREAM("Right Infrared Seq: " << msg->header.seq << std::endl);
     // ROS_INFO_STREAM("Right Infrared Range: " << msg->range << std::endl);
     if (msg->range > 0.00640) {
          ROS_INFO_STREAM("Something to the right!" << std::endl);
     } else {
          ROS_INFO_STREAM("Nothing to the right!" << std::endl);
     }
}

int main (int argc, char** argv) {
     ros::init(argc, argv, "/test_drive_controller/sens_ir/right");
     ros::NodeHandle nh;
     ros::Subscriber sub_l = nh.subscribe("/test_drive_controller/sens_ir/left", 1000, &leftCallback);
     ros::Subscriber sub_r = nh.subscribe("/test_drive_controller/sens_ir/right", 1000, &rightCallback);

     ros::spin();
     return 0;
}
