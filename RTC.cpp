#include "RTC.h"


String time = "";
RTC::RTC()
{
	Serial.begin(9600);
}


RTC::~RTC()
{
}

String RTC::get_time(virtuabotixRTC & myRTC)
{
	myRTC.updateTime();
	time = String(myRTC.hours) + ":" + String(myRTC.minutes) + ":" + String(myRTC.seconds)+"                                  ";
	return time;
}
