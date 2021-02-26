//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//			ECE 477 Lab 2
// Allows control of LED brightness through GPIO on RPi 4 4GB
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//	By Miles Martin, Travis Nickerson & Jesse Perkins
//
//#include "pwm_uniform.h"
#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>


// #define VISIBLE_THRESHHOLD (float) 25/1000 // 25 Hz / 1000 ms ... 
// not really sure if this is the right approach.
// looking for value to pass to 2nd arg. of pwm (the period)

void pwm(float duty_cycle_pct, float period_ms, int *pins[], int num_pins);

const int pin_row[] = {22, 26, 23, 27, 24, 28, 29, 25}; 	// WiringPi pin numbers
								// lined up on breadboard 

const int num_pins = sizeof(pin_row)/sizeof(pin_row[0]);	// Max times to loop

int main (int argc, char *argv[]) {
	

	int brightness = atoi(argv[1]);

	if ((255 < brightness)||(0 > brightness)) {

		printf("Error: please pass an argument between 0 and 255 in decimal.\n");
		return 0;

	} 
	/*
	else { // if input valid

		int child = fork();
		int parent = getppid();

		printf("Child process: %d\n",child);
		printf("Parent process: %d\n",parent);

		if (getpid() == getppid()) {

			printf("Parent process ending!\n");
			return 0;

		} else {

			printf("Child process %d still alive\n", child);

		}

	}
	*/

	float brightness_pct = (float) brightness/255; // between 0 and 1
	printf("Your desired brightness: %f\n",brightness_pct);
	
	int i;
	
	wiringPiSetup();					// init	
	
	for(i = 0; i < num_pins; i++) { 
		
		pinMode(pin_row[i], OUTPUT);
	
	}


	
	while(1) {
		pwm(brightness_pct, 25, pin_row, num_pins);
	}
}

void pwm(float duty_cycle_pct, float period_ms, int *pins[], int num_pins) {
		
	float time_high = duty_cycle_pct * period_ms;

	int i;

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
