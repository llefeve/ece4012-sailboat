#!/usr/bin/env python
# license removed for brevity
import time
import serial
import rospy
from std_msgs.msg import String

def talker():
    pub0 = rospy.Publisher('longitude', String, queue_size=10)
    pub1 = rospy.Publisher('latitude', String, queue_size=10)
    pub2 = rospy.Publisher('speed_knots', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(1) # 1hz

    ser = serial.Serial(
        port = '/dev/ttyACM0',
        baudrate=9600,	
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS
    )

    ser.isOpen()
    longitude = latitude = speed = ""
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
	out = out.split("\n")
	for entry in out:
		if (entry.split(",")[0]=="$GPRMC"):
			arr = entry.split(",")
			print arr
			if (arr[2]!="" and arr[3]!= ""):
			    latitude = str(int(float(arr[3][:2]))+(float(arr[3][2:])/60.0))+" "+arr[4]
			    pub0.publish(latitude)			
			if (arr[4]!="" and arr[5]!= ""):
 			    longitude = (-1) * str(int(float(arr[5][:3]))+(float(arr[5][3:])/60.0))+" "+arr[6]
			    pub1.publish(longitude)
			if (arr[7]!=""):
			    velocity = arr[7]
			    pub2.publish(velocity)
			#rospy.loginfo(out)
			
			#rospy.loginfo("lat:"+latitude+", long:"+longitude+", speed:"+velocity)
			
			pub1.publish(longitude)
			
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
