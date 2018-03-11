# HABalloon
Flying Arduino Balloon tracker KD2NDR

This is a Arduino based balloon tracker that transmits telemetry on JT4, JT9, JT65 and WSPR.
There is a lot of documentation in the code.
This is my first Arduino code project, I have no formal coding education.


Hardware: 
	- Arduino
	- AD9850 DDS
	- TMP36 temperature sensor (optional)
	- any NMEA capable GPS receiver.
	- power source (solar and/or battery)


Features: 
	- AD9850 for signal generation
	- optional switching for RF amplifier
	- temperature monitoring
	- system voltage monitoring
	- GPS based automatic QTH, altitude and transmission timing.


Features to come:
	- DDS frequency stability based off GPS clock or PPS signal
	- PCB board to come when software kinks are worked out
	
	
ToDo:
	- cleanup and streamline code
	- DDS frequency stability
	