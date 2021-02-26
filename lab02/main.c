#include "pwm.h"

#define VISIBLE_THRESHHOLD (float) 25/1000 // 25 Hz / 1000 ms ... 
// not really sure if this is the right approach.
// looking for value to pass to 2nd arg. of pwm, the period

const int pin_row[] = {22, 26, 23, 27, 24, 28, 29, 25}; 	// WiringPi pin numbers
								// lined up on breadboard 

const int num_pins = sizeof(pin_row)/sizeof(pin_row[0]);	// Max times to loop


int main (int argc, char *argv[]) {
	
	int brightness = 
	
	
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
