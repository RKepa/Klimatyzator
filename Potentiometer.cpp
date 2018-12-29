#include "Potentiometer.h"


int potentiometer_buffer = 10; // bufor odczytu potecjometru, d
 


Potentiometer::Potentiometer()
{
}


Potentiometer::~Potentiometer()
{
}

int Potentiometer::get_menu_position(int & potetiometer_value, int & menu_size,int & current_pos)
{

	int borderline = 1050 / menu_size;
	for (int i = 1; i <= menu_size; ++i) {
		if (potetiometer_value <= (borderline*i + potentiometer_buffer) && potetiometer_value >= (borderline*i - potentiometer_buffer))
		{
			return current_pos;
		}
	}

	 
	return potetiometer_value/borderline;
}
