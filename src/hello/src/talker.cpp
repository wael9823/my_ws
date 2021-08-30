#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<std_msgs::String>("chatter",10);
   
    std_msgs::String msg;
    msg.data = "Awesome";

    ros::Rate poll(100);
    while(pub.getNumSubscribers()<=1){
        poll.sleep();
        pub.publish(msg);
        ros::spinOnce();
        ROS_INFO("0. %s ", msg.data.c_str());
        if(pub.getNumSubscribers()==1){
            while(pub.getNumSubscribers()==1){
                poll.sleep();
                pub.publish(msg);
                ros::spinOnce();
                ROS_INFO("1. %s ", msg.data.c_str());
            }
            ros::shutdown();
        }
    }

    return 0;
}