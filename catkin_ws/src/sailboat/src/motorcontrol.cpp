#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/UInt16.h"

int desHeading, actHeading;
void desHeadingCallback(const std_msgs::Int32::ConstPtr& msg)
{
	ROS_INFO("I heard: [%d]", msg->data);
	desHeading = msg->data;
}

void actHeadingCallback(const std_msgs::Int32::ConstPtr& msg)
{
	ROS_INFO("I heard: [%d]", msg->data);
	actHeading = msg->data;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "heading_listener");
  ros::NodeHandle n;

  ros::Subscriber des_heading = n.subscribe("DESIRED_HEADING", 1000, desHeadingCallback);
  ros::Subscriber act_heading = n.subscribe("NAV_HEADING", 1000, actHeadingCallback);
  ros::Publisher rudder = n.advertise<std_msgs::UInt16>("rudderServo", 1000);
  ros::Publisher lidar = n.advertise<std_msgs::UInt16>("lidarServo", 1000);
  ros::Publisher sail = n.advertise<std_msgs::UInt16>("sailServo", 1000);

  ros::Rate loop_rate(10);

  int diff;
  int lidarAngle = 0;
  bool forward = true;

  std_msgs::UInt16 init;
  init.data = 0;
  lidar.publish(init);

  std_msgs::UInt16 setSail;
  init.data = 180;
  sail.publish(setSail);
  ros::spinOnce();

  while(ros::ok)
  {
	diff = desHeading - actHeading;

	std_msgs::UInt16 msg;
	std_msgs::UInt16 ldr;
	if(diff >= 80)
	{
		msg.data = 15;
	}
	else if((diff >= 50) & (diff < 80))
	{
		msg.data = 30;
	}
	else if((diff >= 20) & (diff < 50))
	{
		msg.data = 60;
	}
	else if((diff >= 5) & (diff < 20))
	{
		msg.data = 75;
	}
	else if(diff < -80)
	{
		msg.data = 165;
	}
	else if(diff < -50)
	{
		msg.data = 150;
	}
	else if(diff < -20)
	{
		msg.data = 120;
	}
	else if(diff < -5)
	{
		msg.data = 105;
	}
	else
		msg.data = 90;

	if(forward)
		lidarAngle = lidarAngle + 2;
	else
		lidarAngle = lidarAngle - 2;

	if(lidarAngle >= 180)
		forward = false;
	if(lidarAngle <= 0)
		forward = true;

	ldr.data = lidarAngle;

	lidar.publish(ldr);
	rudder.publish(msg);

	ros::spinOnce();

	loop_rate.sleep();
  }

  ros::spin();

  return 0;
}
