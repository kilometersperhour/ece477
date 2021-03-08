//#include "pwm_gaugelike.h"
#include <sys/types.h> // is this needed for fork()?
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h> // for open()
#include <sys/stat.h>  // so is this
#include <fcntl.h>     // and this

#include <wiringPi.h>

#define HOLD_STATE 1000  // Hold the LEDs at a certain state for this many millis

void pwm(float duty_cycle_pct[], float period_ms, int pins[]);

const char args_error_string[] = "Error. Arguments passed. Do not pass arguments.";

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
	
	if (argc != 1) {
		printf("%s", args_error_string);
		return 1;
	} 
	
	char string_buffer[4];
	float stress;
	int open_file_fd;
	
	float load_diff[8];
	float factor_of_divs[8];
    	int i;	

	wiringPiSetup();  // init	
	for(i = 0; i < num_pins; i++) { 
		pinMode(pin_row[i], OUTPUT);
	}

	while(1) {

		open_file_fd = open("/proc/loadavg",O_RDONLY);
		read(open_file_fd, string_buffer, 4);
		stress = strtof(string_buffer, NULL); // string to float()
//		printf("%f is stress\n",stress);
		
		for(i = 0; i < 8; i++) {
			if(i == 0) {
				// Takes input to calculate first value in load_dif
				load_diff[0] = stress - divs_array[0];        
			}
			else {
				// Uses previous load_dif value to calculate current value
            			load_diff[i] = load_diff[i - 1] - divs_array[i];           
			}
		}
		
		for(i=0; i<8; i++) {
	//		printf("%f \n", load_diff[i]);
		}
		
		// printf("I made it out!!\n");

		// if load is greater than 1, and next is not, 
		// then set that last pin to be equal to the percent brightness of the load
		// send it a single pin pin_row[i]

		for(int i = 0; i < 8; i++) {			// Runs once per pin (8 pins)
			// If the factor_of_divs is negative, 
			// grab the last pins factor 
			// and set that brightness to the pin
	//		printf("Doing WiringPi pin %d\n", pin_row[i]);
//			if ((divs_array[i] > load_diff[i]) && (i == 0))  { 	
	
			factor_of_divs[i] = load_diff[i]/divs_array[i];

			if (factor_of_divs[i] > 1) {
				factor_of_divs[i] = 1;
			}
			else if (factor_of_divs[i] < 0) {
				factor_of_divs[i] = 0;
			}

		}
	
		for(i=0; i<8; i++) {
	//		printf("%f \n", factor_of_divs[i]);
		}

		pwm(factor_of_divs, 20, pin_row);
		delay(2000);
	}	
}

void pwm(float duty_cycle_pct[], float period_ms, int pins[]) {
		
	float time_high;
	
	int i,j;
//	int num_pins = sizeof(pins)/sizeof(pins[0]);
//	printf("%d is num_pins",num_pins);
//	for (j = 0; j < 500; j++) {
		for (i = 0; i < 8; i++) {
			if (duty_cycle_pct[i] > 0) {
				digitalWrite(pins[i], HIGH);  // set pins; turn on lights
			}
	
			if ((duty_cycle_pct[i] != 1) && (duty_cycle_pct[i] != 0)) {
				time_high = (duty_cycle_pct[i]) * (period_ms);
				delay(time_high);  // keep high appropriately long
			}
			
			if (duty_cycle_pct[i] < 1) {
				digitalWrite(pins[i], LOW);  // clear pins; turn off lights
			}
	
			if ((duty_cycle_pct[i] != 1) && (duty_cycle_pct[i] != 0)) {
				delay(period_ms - time_high);  // keep dark appropriately long
			}
		}
//	}
}
