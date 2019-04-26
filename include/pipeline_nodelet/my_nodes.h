#ifndef PIPELINE_NODELET__MI_NODES_H_
#define PIPELINE_NODELET__MI_NODES_H_

#include "ros/ros.h"
#include "helper.h"
#include <iostream>
#include <nodelet/nodelet.h>
#include "std_msgs/UInt8.h"

namespace pipeline_nodelet{

    class Level1 : public nodelet::Nodelet{
    public:
	Level1(){
	    NODELET_INFO("Level1 node contructed\n");
	};
	~Level1(){
	    NODELET_INFO("Level1 node destrcuted\n");
	};
	virtual void onInit(){
	    ros::NodeHandle& n = getPrivateNodeHandle();
	    pub = n.advertise<std_msgs::UInt8>("pipe_l1_output", 5);
	    timer = n.createTimer(ros::Duration(0.25), &Level1::timerCallback, this);
	    NODELET_INFO("Level1 node created\n");
	};

    private:
	ros::Publisher pub;
	ros::Timer timer;
	unsigned char count=0;
	void timerCallback(const ros::TimerEvent& event){
	    ROS_INFO("timeout triggered\n");
	    std_msgs::UInt8 msg;
	    msg.data = count;
	    pub.publish(msg);
	    count+=1;
	}
    };

    class Level2 : public nodelet::Nodelet{
    public:
	Level2(){
	    NODELET_INFO("Level2 node contructed\n");
	};
	~Level2(){
	    NODELET_INFO("Level2 node destructed\n");
	};
	virtual void onInit(){
	    ros::NodeHandle& n = getPrivateNodeHandle();
	    sub = n.subscribe("pipe_l1_output", 5, &Level2::drain_callback, this);
	    pub = n.advertise<std_msgs::UInt8>("pipe_l2_output", 5);
	    NODELET_INFO("Level2 node created\n");
	};
    private:
	ros::Publisher pub;
	ros::Subscriber sub;
	void drain_callback(const std_msgs::UInt8::ConstPtr& msg){
	    std_msgs::UInt8 new_msg;
	    new_msg.data = (msg->data)*2;
	    pub.publish(new_msg);
	};	
    };
    
};


#endif
