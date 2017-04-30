#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String

def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    f = open("/dev/ttyACM0", "r")
    while not rospy.is_shutdown():
        text = f.read()
        hello_str = "hello world %s" % text
        print hello_str
        pub.publish(hello_str)
        rate.sleep()
    f.close()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
