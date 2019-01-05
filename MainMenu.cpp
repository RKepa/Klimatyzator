// 
// 
// 

#include "MainMenu.h"
#include "RTC.h"




virtuabotixRTC myRTC(7, 6, 5); //If you change the wiring change the pins here also
RTC this_rtc;
String menu[] = {"Time    ","Temp    ","Fan      ","Position    ","SetTemp    ","SetFan    "};

String MainMenuClass::check_value(int & position) //tutaj odbywa sie zczytywanie z urzadzen
{
	switch (position)
	{
	case 0:
		return this_rtc.get_time(myRTC);
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
