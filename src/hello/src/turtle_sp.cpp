#include "ros/ros.h"
#include "time.h"
#include "std_srvs/Empty.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "turtle_sp");
    ros::NodeHandle n;

    srand((unsigned) time(0));

    int r = rand()%255, b =rand()%255, g=rand()%255;
    ROS_INFO("The colors are r:%d, b:%d, g:%d", r,b,g);
    n.setParam("/turtlesim/background_r",r);
    n.setParam("/turtlesim/background_b",b);
    n.setParam("/turtlesim/background_g",g);

    ros::service::waitForService("/reset",-1);
    std_srvs::Empty lol;
    ros::service::call("/reset",lol);
    ROS_INFO("Ran the service\n");
    ros::spin();
    return 0;
}