//#include "pwm_gaugelike.h"
#include <sys/types.h> // is this needed for fork()?
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h> // for open()
#include <sys/stat.h>  // so is this
#include <fcntl.h>     // and this

#include <wiringPi.h>

void pwm(float duty_cycle_pct, float period_ms, int pin);

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
			printf("%f \n", load_diff[i]);
		}
		
		// printf("I made it out!!\n");

		// if load is greater than 1, and next is not, 
		// then set that last pin to be equal to the percent brightness of the load
		// send it a single pin pin_row[i]

		for(int i = 0; i < 8; i++){			// Runs once per pin (8 pins)
			// If the factor_of_divs is negative, 
			// grab the last pins factor 
			// and set that brightness to the pin
			printf("Doing WiringPi pin %d\n", pin_row[i]);
			if (divs_array[i] > load_diff[i]) { 	
				// 1ms to update LEDS "instantly" (very quickly)
				pwm((divs_array[i-1]/load_diff[i-1]), 1, pin_row[i-1]);
				i = 0;
				delay(1); // Wait 2 seconds
		
			} 
			// Seg fault protection if pin0 has greater smaller load than divs_array
			else if ((divs_array[i] > load_diff[i]) && (i == 0)) {	
				delay(1);			
			} else {
				// Else set pin value to 1i
				pwm(1, 1, pin_row[i]);	
			}
		}

		delay(2000);
//		return 0;
		
	}	
}

void pwm(float duty_cycle_pct, float period_ms, int pin) {
		
	float time_high = duty_cycle_pct * period_ms;
//	int i;
//	int num_pins = sizeof(pins)/sizeof(pins[0]);
	while(1) {
		//for(i = 0; i < num_pins; i++) {
		digitalWrite(pin, HIGH);  // set pins; turn on lights
		//}
		delay(time_high);  // keep high appropriately long
		//for(i = 0; i < num_pins; i++) {
		digitalWrite(pin, LOW);	 // clear pins; turn off lights
		//}
		delay(period_ms - time_high);  // keep dark appropriately long
	}
}

