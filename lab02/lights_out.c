/*
*	This code has been modified from 
*	http://wiringpi.com/examples/blink/
*	and is I.P. of Miles Martin.
*/

#include <wiringPi.h>

const int pin_row[] = {22, 26, 23, 27, 24, 28, 29, 25}; 	// WiringPi pin numbers
								// lined up on breadboard 

const int num_pins = sizeof(pin_row)/sizeof(pin_row[0]);	// Max times to loop

int main (void) {
	int i;
	
	wiringPiSetup();
	
	for(i = 0; i < num_pins; i++) { 
		
		pinMode(pin_row[i], OUTPUT);
	
	}
	
	for(i = 0; i < num_pins; i++) {	
		
		digitalWrite(pin_row[i], LOW);			// turn off pins
		delay(1000/num_pins);				// turn off all pins in 1s
	
	}
	
	return 0;

}
