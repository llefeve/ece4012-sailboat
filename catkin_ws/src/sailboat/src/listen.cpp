#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/String.h"
#include "stdlib.h"
#include <string>


int msg2, msg3, msg4, msg5, msg6, msg7, msg8;
std::string cmps, roll, pitch;
bool takePic = false;
int counter = 0;
void chatterCallback(const std_msgs::Int32::ConstPtr& msg)
{
	//ROS_INFO("I heard: [%d]", msg->data);
	msg2 = msg->data;

}

void lidarCallback(const std_msgs::Int32::ConstPtr& msg)
{
	//ROS_INFO("I heard: [%d]", msg->data);
	msg3 = msg->data;
	if((msg3 < 10) && (takePic == false))
		takePic = true;

}

void encoderCallback(const std_msgs::Int32::ConstPtr& msg)
{
	//ROS_INFO("I heard: [%d]", msg->data);
	msg4 = msg->data;

}

void sonarCallback(const std_msgs::Int32::ConstPtr& msg)
{
	//ROS_INFO("I heard: [%d]", msg->data);
	msg5 = msg->data;

}

void compassCallback(const std_msgs::String::ConstPtr& msg)
{
	//ROS_INFO("I heard: [%d]", msg->data);
	cmps = msg->data;

}

void rollCallback(const std_msgs::String::ConstPtr& msg)
{
	//ROS_INFO("I heard: [%d]", msg->data);
	roll = msg->data;

}

void pitchCallback(const std_msgs::String::ConstPtr& msg)
{
	//ROS_INFO("I heard: [%d]", msg->data);
	pitch = msg->data;

}

int main(int argc, char **argv)
{
	 
	ros::init(argc, argv, "sensor_listener");
	ros::NodeHandle n;
	ros::Publisher pub1 = n.advertise<std_msgs::Int32>("finalBin", 1000);
	ros::Publisher pub2 = n.advertise<std_msgs::Int32>("finalLidar", 1000);
	ros::Publisher pub3 = n.advertise<std_msgs::Int32>("finalEncoder", 1000);
	ros::Publisher pub4 = n.advertise<std_msgs::Int32>("finalSonar", 1000);
	ros::Publisher pub5 = n.advertise<std_msgs::String>("finalCompass", 1000);
	ros::Publisher pub6 = n.advertise<std_msgs::String>("finalRoll", 1000);
	ros::Publisher pub7 = n.advertise<std_msgs::String>("finalPitch", 1000);
	ros::Subscriber sub1 = n.subscribe("bin", 1000, chatterCallback);
	ros::Subscriber sub2 = n.subscribe("lidar", 1000, lidarCallback);
	ros::Subscriber sub3 = n.subscribe("encoder", 1000, encoderCallback);
	ros::Subscriber sub4 = n.subscribe("sonar", 1000, sonarCallback);
	ros::Subscriber sub5 = n.subscribe("compass", 1000, compassCallback);
	ros::Subscriber sub6 = n.subscribe("roll", 1000, rollCallback);
	ros::Subscriber sub7 = n.subscribe("pitch", 1000, pitchCallback);


	ros::Rate loop_rate(10);

	while(ros::ok)
	{
		// finalBin publisher msg
		std_msgs::Int32 fmsg1;
		fmsg1.data = msg2;

		// finalLidar publisher msg
		std_msgs::Int32 fmsg2;
		fmsg2.data = msg3;

		// finalEncoder publisher msg
		std_msgs::Int32 fmsg3;
		fmsg3.data = msg4;

		// finalSonar publisher msg
		std_msgs::Int32 fmsg4;
		fmsg4.data = msg5;

		//finalCompass publisher msg
		std_msgs::String fmsg5;
		fmsg5.data = cmps;

		//finalRoll publisher msg
		std_msgs::String fmsg6;
		fmsg6.data = roll;

		//finalPitch publisher msg
		std_msgs::String fmsg7;
		fmsg7.data = pitch;


		// publish finalBin
		//ROS_INFO("%d", fmsg1.data);
		pub1.publish(fmsg1);

		// publish finalLidar
		//ROS_INFO("%d", fmsg2.data);
		pub2.publish(fmsg2);

		// publish finalEncoder
		//ROS_INFO("%d", fmsg3.data);
		pub3.publish(fmsg3);

		// publish finalSonar
		//ROS_INFO("%d", fmsg4.data);
		pub4.publish(fmsg4);

		// publish finalCompass
		//ROS_INFO("%d", fmsg4.data);
		pub5.publish(fmsg5);

		// publish finalCompass
		//ROS_INFO("%d", fmsg4.data);
		pub6.publish(fmsg6);

		// publish finalCompass
		//ROS_INFO("%d", fmsg4.data);
		pub7.publish(fmsg7);

/*		if(takePic && (counter >= 500))
		{
			system("rosrun sailboat camera.py");
			printf("picture taken");
			takePic = false;
			counter = 0;
		}
		counter = counter + 1;
*/
		ros::spinOnce();

		loop_rate.sleep();
	}

	ros::spin();

	return 0;
}
