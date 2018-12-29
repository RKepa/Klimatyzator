// MainMenu.h

#ifndef _MAINMENU_h
#define _MAINMENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <LiquidCrystal_I2C.h>


 class MainMenuClass
{
 protected:
	 String check_value(int & position);
 public:
	void init(LiquidCrystal_I2C & lcd);
	void show_position(LiquidCrystal_I2C & lcd, int & pos);

	
};

extern MainMenuClass main_menu;

#endif
