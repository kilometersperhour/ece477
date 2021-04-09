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

void pwm(float duty_cycle_pct[], float period_ms, const int pins[]);

const char args_error_string[] = "Error. Arguments passed. Do not pass arguments.\n";

const int pin_row[8] = { // map GPIO to corresponding wiringPi pins 0-7
0,  // GPIO 17
1,  // GPIO 18
2,  // GPIO 27
3,  // GPIO 22
4,  // GPIO 23
5,  // GPIO 24
6,  // GPIO 25
7   // GPIO 4
};

const int num_pins = sizeof(pin_row)/sizeof(pin_row[0]);  // Max times to loop

const float divs_array[8] = { // an array of divisors
4./128,  // Where each increasing LED must light up when the load doubles,
4./64,   // each value of this array doubles in kind.
4./32,   // The values have been multiplied by a factor of four
4./16,   // because the max load is 4/4.
4./8,    // The values are divided by 255 to normalize them
4./4,    
4./2,    
4.
};

int main (int argc, char *argv[]) {
	
	if (argc != 1) {
		printf("%s", args_error_string);
		return -1;
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
		
		// 4/5/2021
		for (i = 0; i < 8; i++) {
			if (stress > divs_array[i]) {
				load_diff[i] = 1;
			} else if (stress > 0) {
				load_diff[i] = stress/divs_array[i];
				while (i < 8-1) {
					load_diff[i+1] = 0;
				}
			}
			printf("%f, ", load_diff[7-i]);
		}
		printf("[7..0]\n");

		pwm(load_diff, 20, pin_row);
	}	
}

void pwm(float duty_cycle_pct[], float period_ms, const int pins[]) {
		
	float time_high;
	int dim_led = 7; // the LED we will perform PWM on
	int i;
//	int num_pins = sizeof(pins)/sizeof(pins[0]);
//	printf("%d is num_pins",num_pins);
//	for (j = 0; j < 500; j++) {
	for (i = 0; i < 8; i++) {
		if (duty_cycle_pct[i] == 1) {
			digitalWrite(pins[i], HIGH);  // set pins; turn on lights
		} else if (duty_cycle_pct[i] == 0 ) {
			digitalWrite(pins[i], LOW);  // clear pins; turn off lights
		} else {
			dim_led = i;
		}
	}

	time_high = (duty_cycle_pct[dim_led]) * (period_ms);
	
	for (i = 0; i < 50; i++) {

		digitalWrite(pins[dim_led], HIGH);  // turn on LED
		delay(time_high);  // keep lit appropriately long
		
		digitalWrite(pins[dim_led], LOW);  // turn off LED
		delay(period_ms - time_high);  // keep dark appropriately long
	}
//	}
}
