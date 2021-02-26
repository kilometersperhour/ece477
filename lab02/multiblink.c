/*
*	This code has been modified from 
*	http://wiringpi.com/examples/blink/
*	and is I.P. of Miles Martin.
*/

#include <wiringPi.h>

int pin_row[] = {22, 26, 23, 27, 24, 28, 29, 25};

int main (void) {
	wiringPiSetup();
	
	pinMode(0, OUTPUT);
	
	while(1) {
	
		for(int i = 0; i < 8; i++) {
		
			digitalWrite(pin_row[i], HIGH);
			delay(500);
	
		}
	
		for(int i = 0; i < 8; i++) {
		
			digitalWrite(pin_row[i], LOW);
			delay(500);
	
		}
	}
	return 0;
}
