#include "LCD.h"


static LiquidCrystal_I2C lcd(0x27, 16, 4);
LCD::LCD()
{
	lcd.init();
}


LCD::~LCD()
{
}
