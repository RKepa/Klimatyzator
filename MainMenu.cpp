// 
// 
// 

#include "MainMenu.h"
#include "RTC.h"
#include "FAN.h"




virtuabotixRTC myRTC(7, 6, 5); //If you change the wiring change the pins here also
RTC this_rtc;
String menu[] = {"Time       ","Temp       ","Fan (big)      ","Fan (small)     ","Optimal Temp"};
double temperature;

String MainMenuClass::check_value(int & position) //tutaj odbywa sie zczytywanie z urzadzen
{
	switch (position)
	{
	case 0:
		return this_rtc.get_time(myRTC);
		break;
	case 1:
		return String(temperature).substring(0,2) + " *C      ";
		break;
	case 2:
		return static_fan.is_big_working();
		break;
	case 3:
		return static_fan.is_small_working();
		break;
	case 4:
		return String(static_fan.get_temperature_limit()).substring(0, 2) + " *C      ";
		break;
	default:
		break;
	}
	return "                 ";
}

void MainMenuClass::init(LiquidCrystal_I2C & lcd) //inicjacja menu
{
	lcd.setCursor(0, 0);
	lcd.print(menu[0]);
	lcd.setCursor(0, 1);
	lcd.print("");
	
}

void MainMenuClass::show_position(LiquidCrystal_I2C & lcd, int & pos)
{
	lcd.setCursor(0, 0);
	lcd.print(menu[pos]);
	lcd.setCursor(0, 1);
	lcd.print(check_value(pos));
}

void MainMenuClass::set_temperature(double temp) {
	if (!isnan(temp)) {
		temperature = temp;
	}
	
}
