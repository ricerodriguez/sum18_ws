#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>

void transformPoint (const tf::TransformListener& listener) {
     geometry_msgs::PointStamped ir_point_left;
     geometry_msgs::PointStamped ir_point_right;
     ir_point_left.header.frame_id = "sens_ir_left_link";
     ir_point_right.header.frame_id = "sens_ir_right_link";
     ir_point_left.header.stamp = ros::Time();
     ir_point_right.header.stamp = ros::Time();

     ir_point_left.point.x = 1.0;
     ir_point_left.point.y = 0.2;
     ir_point_left.point.z = 0.0;

     ir_point_right.point.x = 1.0;
     ir_point_right.point.y = 0.2;
     ir_point_right.point.z = 0.0;

     try {
          geometry_msgs::PointStamped base_point_left;
          geometry_msgs::PointStamped base_point_right;
          listener.transformPoint("chassis", ir_point_left, base_point_left);
          listener.transformPoint("chassis", ir_point_right, base_point_right);
          ROS_INFO("Left IR Sensor: (%.2f, %.2f, %.2f) ----> Chassis: (%.2f, %.2f, %.2f) at time %.2f", ir_point_left.point.x, ir_point_left.point.y, ir_point_left.point.z, base_point_left.point.x, base_point_left.point.y, base_point_left.point.z, base_point_left.header.stamp.toSec());
          ROS_INFO("Right IR Sensor: (%.2f, %.2f, %.2f) ----> Chassis: (%.2f, %.2f, %.2f) at time %.2f", ir_point_left.point.x, ir_point_right.point.y, ir_point_right.point.z, base_point_right.point.x, base_point_right.point.y, base_point_right.point.z, base_point_right.header.stamp.toSec());
     } catch (tf::TransformException& err) {
          ROS_ERROR_STREAM("ERROR: " << err.what());
     }
}

int main (int argc, char** argv) {
     ros::init (argc, argv, "robot_tf_listener");
     ros::NodeHandle nh;

     tf::TransformListener listener(ros::Duration(10));
     ros::Timer timer = nh.createTimer(ros::Duration(1.0), boost::bind(&transformPoint, boost::ref(listener)));

     ros::spin();
}
