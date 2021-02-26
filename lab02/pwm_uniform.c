#include "pwm_uniform.h"

extern void pwm(float duty_cycle_pct, float period_ms, int pins[]) {
	
	float time_high = duty_cycle_pct * period_ms;

	int i;

	int num_pins = sizeof(pins)/sizeof(pins[0]);

	while(1) {
	
		for(i = 0; i < num_pins; i++) {
		
			digitalWrite(pins[i], HIGH);		// set pins; turn on lights
	
		}

		delay(time_high);						// keep high appropriately long

		for(i = 0; i < num_pins; i++) {
		
			digitalWrite(pins[i], LOW);		// clear pins; turn off lights
	
		}

		delay(period_ms - time_high);			// keep dark appropriately long
	}
	return 0;
}
