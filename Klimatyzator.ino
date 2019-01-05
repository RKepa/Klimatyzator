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
#include <avr/sleep.h>
#include <time.h>


#define POTENCJOMETR_PIN PC1
#define KEY1 (1<<PD2)

const int LED = 13;                         //LED on pin 13
const int LED1 = 12;
uint16_t c = 1;                             //licznik debauncera
static int menu_pos = 0;                    //poczatkowa pozycja w menu
int menusize = 6;                           //wielkosc menu

LiquidCrystal_I2C lcd(0x27, 16, 4);

void setup()
{
//---------------------------
	for (byte i = 0; i < 20; i++) {    //make all pins inputs with pullups enabled
		pinMode(i, INPUT_PULLUP);
	}
	
	lcd.init();
	lcd.backlight();
	Serial.begin(9600);


	cli();                        //Zatrzymanie przerwan
	TCCR1A = 0;					  // set entire TCCR1A register to 0
	TCCR1B = 0;                   // same for TCCR1B
	TCNT1 = 0;                    //initialize counter value to 0
	// set compare match register for 10hz increments
	OCR1A = 1562;				  // = (16*10^6) / (1*1024) - 1 (must be <65536) | wartosc przez ktora dzielony jest preskaler
	// turn on CTC mode | jezeli dojdzie  do porownanej liczby to sie zeruje
	TCCR1B |= (1 << WGM12);
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	// Set CS10 and CS12 bits for 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);
	Serial.println("poszlo");
	

//--------------------------przerwanie INT0 uspienie procesora---------------------------------------------------------------

	DDRD &= ~(1 << PD2);    // INT0: input...
	PORTD |= (1 << PD2);    // ...with pullup.
	//disable brown-out detection while sleeping
	EICRA = 0;
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	sei();//allow interrupts
	pinMode(LED1, OUTPUT);
	pinMode(LED, OUTPUT);          //make the led pin an output
	digitalWrite(LED, LOW);        //drive it low so it doesn't source current

}

void goToSleep(void)
{
	lcd.clear();
	lcd.noBacklight();
	digitalWrite(LED, HIGH);
	delay(2000);
	digitalWrite(LED, LOW);
	byte adcsra = ADCSRA;          //save the ADC Control and Status Register A
	ADCSRA = 0;                    //disable the ADC
				//configure INT0 to trigger on falling edge
	//sleep_bod_disable();           //for AVR-GCC 4.3.3 and later, this is equivalent to the previous 4 lines of code
	EIMSK |= (1 << INT0);
	sleep_enable();                      
	sleep_cpu();                   //go to sleep
	sleep_disable();               //wake up here
	ADCSRA = adcsra;               //restore ADCSRA
	digitalWrite(LED, HIGH);
	delay(2000);
	digitalWrite(LED, LOW);
	lcd.backlight();
}
void debaunce(void) {
	while (true)
	{
		if (!c && !(PIND & KEY1)) {
			c = 1;
			//break;
		}
		else if (c && (PIND & KEY1)) {

			if (!++c) {
				c = 1;
				return;
			}
		}

	}
}

ISR(INT0_vect)  //przerwanie INT0
{
	EIMSK = 0;
	debaunce();
	//Serial.println("asdasd");
}

ISR(TIMER1_COMPA_vect) {// przerwanie z timera wykonuje sie ok 0.1 sekundy
	OCR1A = 1562;
	int wartosc = analogRead(POTENCJOMETR_PIN);
	//Serial.println(wartosc);
	menu_pos = potentiometer.get_menu_position(wartosc, menusize,menu_pos); //odczytanie z potecjometru pozycji w menu
	//Serial.println(menu_pos);



}
// Add the main program code into the continuous loop() function
void loop()
{
	main_menu.show_position(lcd, menu_pos);
	if (!(PIND & KEY1)) {
		debaunce();
			goToSleep();
	}

}
