#ifndef LINE_FOLLOWER_H_
#define LINE_FOLLOWER_H_

#include <ros/ros.h>
#include <sensor_msgs/Illuminance.h>
#include <geometry_msgs/Twist.h>

typedef sensor_msgs::Illuminance::ConstPtr constIllumPtr;


class LineFollower {
public:
     LineFollower(ros::NodeHandle* nodehandle);
     void followTheLine();
private:
     ros::NodeHandle nh_;
     ros::Subscriber sub_left_, sub_right_;
     ros::Publisher pub_;
     sensor_msgs::Illuminance infraleft_, infraright_;
     void initializeSubscribers();
     void initializePublishers();
     void sensSubscriberCallback(const constIllumPtr&);
};

#endif
