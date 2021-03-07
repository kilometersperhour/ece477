//#include "pwm_gaugelike.h"
#include <sys/types.h> // is this needed for fork()?
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

void pwm(float duty_cycle_pct, float period_ms, int *pins[]);

const int pin_row[8] = { // map GPIO-7 to corresponding wiringPi pins
30,   // GPIO 0
31,   // GPIO 1
8,    // GPIO 2
9,    // GPIO 3
7,    // GPIO 4
21,   // GPIO 5
22,   // GPIO 6
11    // GPIO 7
};

const int num_pins = sizeof(pin_row)/sizeof(pin_row[0]);  // Max times to loop

const float divs_array[8] = { // an array of divisors
4./255,  // Where each increasing LED must light up when the load doubles,
8./255,  // each value of this array doubles in kind.
16./255,  // The values have been multiplied by a factor of four
32./255,  // because the max load is 4/4.
64./255, // The values are divided by 255 to normalize them
128./255, // 255 is the sum of 2^0 through 2^7, representing the
256./255, // corresponding weights of each LED's brightness.
512./255
};

int main (int argc, char *argv[]) {
	
	int open_file_fd 

	float stress = strtof(string_buffer, NULL); // string to float()
	char args_error_string[]   = "Error. Arguments passed. Do not pass arguments.";
//	char stress_error_string[] = "Error. Stress has exceeded 4.0/4.0.\n";

	if (argc != 2) {

		printf("%s", args_error_string);
		return 1;

	} else {
		printf("%f",stress);
	}
/*
float brightness_pct = (float) brightness/255; // between 0 and 1
	printf("Your desired brightness: %f\n",brightness_pct);
	
	int i;
	
	wiringPiSetup();					// init	
	
	for(i = 0; i < num_pins; i++) { 
		
		pinMode(pin_row[i], OUTPUT);
	
	}


	
	while(1) {
		pwm(brightness_pct, 25, &pin_row);
	}
}

void pwm(float duty_cycle_pct, float period_ms, int *pins[]) {
		
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

*/
}




/*	for(i = 0; i < num_pins; i++) {				
		
		pinMode(pin_row[i], OUTPUT);			// set pin_row pins to OUTPUT
	
	}


	//while(1) {
	
		for(i = 0; i < 8; i++) {
		
			digitalWrite(pin_row[i], HIGH);		// set pins; turn on lights
			delay(500);
	
		}
	
		for(i = 0; i < 8; i++) {
		
			digitalWrite(pin_row[i], LOW);		// clear pins; turn off lights
			delay(500);
	
		}
	//}
	return 0;
}
*/
