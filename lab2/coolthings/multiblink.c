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
	
	wiringPiSetup();					// init
	
	for(i = 0; i < num_pins; i++) {				
		
		pinMode(pin_row[i], OUTPUT);			// set pin_row pins to OUTPUT
	
	}


	while(1) {
	
		for(i = 0; i < 8; i++) {
		
			digitalWrite(pin_row[i], HIGH);		// set pins; turn on lights
			delay(500);
	
		}
	
		for(i = 0; i < 8; i++) {
		
			digitalWrite(pin_row[i], LOW);		// clear pins; turn off lights
			delay(500);
	
		}
	}
	return 0;
}
