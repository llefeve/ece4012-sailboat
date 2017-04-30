#!/usr/bin/env python
# license removed for brevity
import time
import serial
import rospy
from std_msgs.msg import String

def talker():
    pub0 = rospy.Publisher('compass', String, queue_size=10)
    pub1 = rospy.Publisher('pitch', String, queue_size=10)
    pub2 = rospy.Publisher('roll', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(1) # 1hz

    ser = serial.Serial(
       #port='/dev/serial/by-id/usb-Silicon_Labs_CP2102_USB_to_UART_Bridge_Controller_0001-if00-port0',
        port = "/dev/ttyUSB0",
        baudrate=19200,	
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS
    )

    ser.isOpen()
    compass = pitch = roll = ""
    while not rospy.is_shutdown():
	input=0
	line = 1
	while line :
		out = ''
		while ser.inWaiting() > 0:
		    	out += ser.read()
			if out.startswith('$') != 1:
				out = ''
		if out != '':
		  	line = 0
			#ex: $C60.3P-15.1R165.2*42
			print out
			#Compass Parse
			compass = out.split("P")[0].split("C")[1]
			#Pitch Parse
			pitch = out.split("R")[0].split("P")[1]
			#Roll Parse
			roll = out.split("*")[0].split("R")[1]
			#rospy.loginfo(out)
			rospy.loginfo("C:"+compass+", P:"+pitch+", R:"+roll)
			pub0.publish(compass)
			pub1.publish(pitch)
			pub2.publish(roll)

        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
