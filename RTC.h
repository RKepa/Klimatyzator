#pragma once

#include <virtuabotixRTC.h>
class RTC
{
public:
	RTC();
	~RTC();
	static String get_time(virtuabotixRTC & myRTC);
};

extern RTC static_rtc;