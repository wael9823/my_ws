#include "ros/ros.h"
#include "std_msgs/String.h"

void chattercb(const std_msgs::String::ConstPtr &message){
    static int i=0;
    if(i<5){
        ROS_INFO("Hello world! This is %s", message->data.c_str());
        i++;
    }
    else{
        ros::shutdown();
    }
}

int main(int argc, char** argv){
    ros::init(argc,argv,"listener");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatter",10,chattercb);
    ros::spin();
    return 0;
}