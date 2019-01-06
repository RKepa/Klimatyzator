#include "FAN.h"


double temperature_limit = 23.00;
FAN::FAN()
{
	Serial.begin(9600);
	
}


FAN::~FAN()
{
}

void FAN::turn_on()
{
	digitalWrite(8, LOW);
}

void FAN::turn_off()
{
	digitalWrite(8, HIGH);
}

void FAN::check_temperature(double temp) {
	if (!isnan(temp) && temp > temperature_limit) {
		digitalWrite(8, LOW);
	}
	else if (!isnan(temp) && temp <= temperature_limit){
		digitalWrite(8, HIGH);
		if (temp = temperature_limit) {
			analogWrite(A0, 255);
		}
		else {
			analogWrite(A0, 0);
		}
	}
}

double FAN::get_temperature_limit() {
	return temperature_limit;
}

String FAN::is_big_working() {
	switch (digitalRead(8))
	{
	case LOW:
		return "is On      ";
		break;
	case HIGH:
		return "is Off     ";
		break;
	default:
		break;
	}
}

String FAN::is_small_working() {
	if (analogRead(A0) > 0) {
		return "is On      ";
	}
	else {
		return "is Off     ";
	}
}