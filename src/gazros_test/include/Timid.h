#ifndef TIMID_CLASS_H_
#define TIMID_CLASS_H_

#include <string>
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <vector>
// #include <actionlib/server/simple_action_server.h>
// #include <gazros_test/Flight.h>
// typedef actionlib::SimpleActionClient<FlightAction> Client;
// typedef actionlib::SimpleActionServer<FlightAction> Server;
// typedef actionlib::SimpleActionServer<gazros_test::Flight>::GoalConstPtr constGoalPtr;
// typedef actionlib::SimpleActionServer<gazros_test::Flight>::ResultConstPtr constResultPtr;
// typedef actionlib::SimpleActionServer<gazros_test::Flight>::FeedbackConstPtr constFeedbackPtr;
typedef sensor_msgs::LaserScan::ConstPtr constLaserScanPtr;
// typedef sensor_msgs::Range::ConstPtr constRangePtr;
// #include <std_msgs/Float32>

class TimidClass {
public:
     TimidClass(ros::NodeHandle* nodehandle);
     void runAway();
     // void actCallback(const constGoalPtr&);
private:
     ros::NodeHandle nh_;
     ros::Subscriber sub_sens_;
     ros::Publisher pub_;
     sensor_msgs::LaserScan scan_;

     // const double laser_freq = 40;

     // Client ac_;
     // Server as_;
     // actionlib::SimpleActionServer<gazros_test::FlightAction> srv_;
     // std::string srv_;

     // gazros_test::FlightGoal goal_;
     // gazros_test::FlightResult result_;
     // gazros_test::FlightFeedback feedback_;
     std::vector<float> vector_;
     float range_;

     void initializeSubscribers();
     void initializePublishers();
     // void initializeActionServers();
     void sensSubscriberCallback(const constLaserScanPtr&);

};

#endif
