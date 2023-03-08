#include <iostream>
#include <ros/ros.h>
#include <cstdio>
#include "echologger.h"
#include <thread>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Range.h>

ros::Publisher pubRange;

void myCallback(const std::string &data){

    std::istringstream data_ss(data);
    std::string line;    
    while (std::getline(data_ss, line)) {
        std::string datatype = line.substr(0,6);
        if(datatype == "$GPDBT") {
            std::istringstream line_ss(line);
            std::string word;
            std::vector<std::string> row;
            while(std::getline(line_ss, word, ',')) {
                row.push_back(word);
            }
            if(row.size() < 4) {
                continue;
            }
            float range = std::stof(row[3]);
            printf("\x1b[1mRange: %.2f\x1b[0m\n", range);

            sensor_msgs::Range rangeMsg;
            rangeMsg.header.stamp = ros::Time::now();
            rangeMsg.header.frame_id = "altimeter";
            rangeMsg.range = range;

            pubRange.publish(rangeMsg);

        }
    }
}

int main(int argc, char **argv){
    ros::init(argc, argv, "echologger_ecs400_node");
    ros::NodeHandle nh;

    std::string port_name = "/dev/ttyUSB0";
    ROS_INFO("\x1b[33mStarting echologger_ecs400_node\x1b[0m");

    pubRange = nh.advertise<sensor_msgs::Range>("/altimeter/depth", 100);

    boost::asio::io_service io;

    auto callback = [](const std::string &data){
        myCallback(data);
    };

    Echologger echologger(io, port_name, 115200, callback);
    std::thread io_thread([&io]() { io.run(); });

    ros::spin();

    io.stop();
    io_thread.join();

    return 0;
}