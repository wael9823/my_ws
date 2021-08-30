#include "ros/ros.h"
#include <stdlib.h>
#include "geometry_msgs/Twist.h"  //velocity msg, topic is /cmd_vel
#include "nav_msgs/Odometry.h"    //position feedback, topic is /odom
#include "turtlesim/Pose.h"

nav_msgs::Odometry location; 

void pose_callback (const nav_msgs::Odometry pos){
    location.pose.pose.position.x = pos.pose.pose.position.x;
    ROS_INFO("Robot position, X:%f\n", pos.pose.pose.position.x); 
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "turtle_walk");
    ros::NodeHandle n;

    const char *clin_vel = argv[1];
    const char *crot_vel = argv[2];
    const char *cdist = argv[3];
    float lin_vel = atof(clin_vel);
    float rot_vel = atof(crot_vel);
    float dist = atof(cdist);
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel",10);
    ros::Subscriber sub = n.subscribe("/odom",10,pose_callback);
    ros::Rate poll(10);

    geometry_msgs::Twist vel;

    while(ros::ok()){
        vel.linear.x = lin_vel;
        vel.linear.y = 0;
        vel.linear.z = 0;
        vel.angular.x = 0;
        vel.angular.y = 0;
        vel.angular.z = rot_vel;
        ROS_INFO("Linear Velocity: %f , Angular Velocity: %f\n", lin_vel, rot_vel);

        if(location.pose.pose.position.x >= dist){
            ROS_INFO("Robot reached destination");
            ROS_WARN("Stopping Turtle Robot");
            break;
        }

        pub.publish(vel);
        ros::spinOnce();
        poll.sleep();
    }

    return 0;
}
