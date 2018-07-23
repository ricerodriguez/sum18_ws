#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main (int argc, char** argv) {
     ros::init (argc, argv, "robot_tf_publisher");
     ros::NodeHandle nh;

     ros::Rate r(100);

     tf::TransformBroadcaster broadcaster;

     while (nh.ok()) {
          broadcaster.sendTransform(tf::StampedTransform(tf::Transform(tf::Quaternion(0,0,0,1),tf::Vector3(-0.02,0.0194,0.0055)),ros::Time::now(),"chassis","sens_ir_left_link"));
          broadcaster.sendTransform(tf::StampedTransform(tf::Transform(tf::Quaternion(0,0,0,1),tf::Vector3(0.0175,0.0194,0.0055)),ros::Time::now(),"chassis","sens_ir_right_link"));
          r.sleep();
     }
}
