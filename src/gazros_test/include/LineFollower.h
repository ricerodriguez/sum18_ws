#ifndef LINE_FOLLOWER_H_
#define LINE_FOLLOWER_H_

#include <ros/ros.h>
#include <sensor_msgs/Illuminance.h>
#include <geometry_msgs/Twist.h>
#include <string>

typedef sensor_msgs::Illuminance::ConstPtr constIllumPtr;
#define STOP  0
#define FWD   1
#define LEFT  2
#define RIGHT 3

class LineFollower {
public:
     LineFollower(ros::NodeHandle* nodehandle);
     void followTheLine();
     void navCenter();
private:
     ros::NodeHandle nh_;
     ros::Subscriber sub_left_, sub_right_;
     ros::Publisher pub_;
     // sensor_msgs::Illuminance infraleft_, infraright_;
     void initializeSubscribers();
     void initializePublishers();
     void leftSubscriberCallback(const constIllumPtr&);
     void rightSubscriberCallback(const constIllumPtr&);
     // const int stop = 0, forward = 1, left = 2, right = 3;
     int dir_;
     double infraleft_, infraright_;
};

#endif
