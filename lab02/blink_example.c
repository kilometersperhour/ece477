/*
*	This code has been slightly modified from 
*	http://wiringpi.com/examples/blink/
*	and is not I.P. of any lab members.
*/

#include <wiringPi.h>

int main (void) {
	wiringPiSetup();
	pinMode(0, OUTPUT);
	while(1) {
		digitalWrite(0, HIGH);
		delay(500);
		digitalWrite(0,  LOW); 
		delay(500);
	}
	return 0;
}
