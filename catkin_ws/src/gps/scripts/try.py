str = "$GPGSV,3,1,11,17,61,355,16,19,54,310,17,06,52,218,18,03,27,076,16*70\n$GPGSV,3,2,11,24,14,313,16,01,15,042,16,02,11,223,17,28,61,109,23*7A\n$GPGSV,3,3,11,30,18,182,18,22,15,052,,11,01,055,*43\n$GPRMC,001747.000,A,3346.8519,N,08424.1032,W,2.02,310.41,190417,,,A*79\n$GPGGA,001748.000,3346.8521,N,08424.1036,W,1,05,1.5,298.0,M,-30.8,M,,0000*62\n$GPGSA,A,3,17,19,06,03,24,,,,,,,,2.5,1.5,2.0*3E"
out = str.split("\n")
for entry in out:
	if (entry.split(",")[0]=="$GPRMC"):
		arr = entry.split(",")
		latitude = arr[3]+" "+arr[4]
		longitude = arr[5]+" "+arr[4]
		velocity = arr[7]
		print latitude
		print longitude
		print velocity
		
