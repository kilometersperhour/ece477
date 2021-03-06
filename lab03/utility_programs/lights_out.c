/*
*	This code has been modified from 
*	http://wiringpi.com/examples/blink/
*	and is I.P. of Miles Martin.
*/

#include <wiringPi.h>

const int pin_row[] = {
30,   // GPIO 0
31,   // GPIO 1
8,    // GPIO 2
9,    // GPIO 3
7,    // GPIO 4
21,   // GPIO 5
22,   // GPIO 6
11    // GPIO 7
};

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
