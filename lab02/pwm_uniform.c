#include <wiringPi.h>
#include "pwm.h"

extern void pwm(int duty_cycle, int period, int pins[]) {
	
	int i;
	num_pins = sizeof(pins)/sizeof(pins[0]);

	while(1) {
	
		for(i = 0; i < num_pins; i++) {
		
			digitalWrite(pin_row[i], HIGH);		// set pins; turn on lights
			delay(500);
	
		}
	
		for(i = 0; i < num_pins; i++) {
		
			digitalWrite(pin_row[i], LOW);		// clear pins; turn off lights
			delay(500);
	
		}
	}
	return 0;
}
