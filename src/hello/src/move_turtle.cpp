#include "ros/ros.h"
#include <stdlib.h>
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

turtlesim::Pose location; 

void pose_callback (const turtlesim::Pose pos){
    ROS_INFO("Robot position, X:%f\n", pos.x);
    location.x = pos.x;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "move_turtle");
    ros::NodeHandle n;

    const char *clin_vel = argv[1];
    const char *crot_vel = argv[2];
    const char *cdist = argv[3];
    float lin_vel = atof(clin_vel);
    float rot_vel = atof(crot_vel);
    float dist = atof(cdist);
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    ros::Subscriber sub = n.subscribe("turtle1/pose",10,pose_callback);
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

        if(location.x>=dist){
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
