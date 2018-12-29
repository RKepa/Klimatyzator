// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Klimatyzator.ino
    Created:	12.11.2018 16:19:40
    Author:     DESKTOP-C5SOV2Q\Radoslaw
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

#include "MainMenu.h"
#include "Potentiometer.h"
#include <virtuabotixRTC.h>
#include <time.h>


#define POTENCJOMETR_PIN PC1

static String menu[8] = { "Temp", "Wetness", "Position", "Time", "Power", "Temp o-c", "Usage Time o-c", "Power o-c" };
String a = "bez";
static int menu_pos = 0;
int menusize = 6;
String comdata = "";
int numdata[7] = { 0 }, j = 0, mark = 0;
// The setup() function runs once each time the micro-controller starts

  LiquidCrystal_I2C lcd(0x27, 16, 4);


void setup()
{
	lcd.init();
	lcd.backlight();
  Serial.begin(9600);
    Serial.println("poszlo");

  cli();//stop interrupts
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B
	TCNT1 = 0;//initialize counter value to 0
	// set compare match register for 1hz increments
	OCR1A = 1562;// = (16*10^6) / (1*1024) - 1 (must be <65536)
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
	// Set CS10 and CS12 bits for 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);
  Serial.println("poszlo");
	sei();//allow interrupts

	

}
ISR(TIMER1_COMPA_vect) {//Interrupt at freq of 1Hz to measure reed switch
	  OCR1A = 1562;
	  int wartosc = analogRead(POTENCJOMETR_PIN);
	  Serial.println(wartosc);
	//volatile int wartosc = analogRead(POTENCJOMETR_PIN);
	  menu_pos = potentiometer.get_menu_position(wartosc, menusize,menu_pos);
		  
  Serial.println(menu_pos);



}
// Add the main program code into the continuous loop() function
void loop()
{
		main_menu.show_position(lcd, menu_pos);
		

		// Start printing elements as individuals


}
