#pragma once

#include <virtuabotixRTC.h>
class FAN
{
public:
	FAN();
	~FAN();
	static void turn_on ();
	static void turn_off();
	static void check_temperature(double temperature);
	//static void set_temperature_limit(double temperature);
	double get_temperature_limit();
	String is_big_working();
	String is_small_working();
};

extern FAN static_fan;
