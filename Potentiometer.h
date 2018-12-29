#pragma once
#ifndef _POTENTIOMETER_h
#define _POTENTIOMETER_h
class Potentiometer
{
public:
	Potentiometer();
	~Potentiometer();
	
	int get_menu_position(int & potetiometer_value,int & menu_size, int & current_pos);
};
extern Potentiometer potentiometer;
#endif
