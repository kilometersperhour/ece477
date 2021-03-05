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
#include <ctype.h>
#include <string.h>
#include <wiringPi.h>

#define BLINK_PERIOD_MS 10

void pwm(float duty_cycle_pct, float period_ms, int *pins[], int num_pins);

const int pin_row[] = {22, 26, 23, 27, 24, 28, 29, 25}; 	// WiringPi pin numbers
								// lined up on breadboard 

const int num_pins = sizeof(pin_row)/sizeof(pin_row[0]);	// Max times to loop

int main (int argc, char *argv[]) {

	if ((2 > argc) || (2 < argc)) {
		
		printf("\nPlease enter exactly two arguments.\n");
		return 0;

	}

	int brightness;

	int i = 0;
	for (i = 0; i < strlen(argv[1]); i++) {

		argv[1][i] = toupper(argv[1][i]);
	
	}
	if ( { // begin conditions for hex input
	('0' == argv[1][0]) && 
	('x' == argv[1][1]) && 
	((('0' <= argv[1][2]) && ('9' >= argv[1][2])) || (('A' <= argv[1][2]) && ('F' >= argv[1][2])) && 
	((('0' <= argv[1][2]) && ('9' >= argv[1][2])) || (('A' <= argv[1][2]) && ('F' >= argv[1][2])) &&  
	} ) // end conditions 
	{ // begin inner statement
	
		brightness = strtol(argv[1], NULL, 16);
		printf("hex\n");

	} else if ( { // begin conditions for octal input
		('0' == argv[1][0]) && 
		(('0' <= argv[1][1]) || ('3' >= argv[1][1])) && 
		(('0' <= argv[1][2]) || ('7' >= argv[1][2])) && 
		(('0' <= argv[1][3]) || ('7' >= argv[1][3])) 
	} ) 	// end conditions
	{	// begin inner statement
	
		brightness = strtol(argv[1], NULL, 8);
		printf("octal\n");

	} else if ( { // begin conditions for decimal input
		('0' == argv[1][0]) && 
		(('0' <= argv[1][1]) || ('9' >= argv[1][1])) && 
		(('0' <= argv[1][2]) || ('9' >= argv[1][2])) && 
		(('0' <= argv[1][3]) || ('9' >= argv[1][3])) 
	} ) 	// end conditions
	{	// begin inner statement	// Hopefully decimal
		
		brightness = strtol(argv[1], NULL, 10);
		printf("decimal\n");

	} else {
		printf("Please correct the format of your input.\n");
		printf("Valid input examples; \n dec: 'lab2a 255', \n oct 'lab2a 0377', \n hex 'lab2a 0xff'");
	}
	


	if ((255 < brightness)||(0 > brightness)) {

		printf("\nError: please pass an argument between 0 and 255 in decimal.\n");
		return 0;

	} 
	else { // if input valid

		int child = fork();
		int parent = getppid();

		// printf("Child process: %d\n",child);
		// printf("Parent process: %d\n",parent);

		if (0 == child) {

		//	printf("Parent process %d ending!\n",child);

		} else {

		//	printf("Child process %d still alive\n", child);
			printf("\nThe program has been forked to the background.\n");
			printf("Before running lab2a again, run 'kill %d'\n",child);

			return 0;

		}

	}

	float brightness_pct = (float) brightness/255; // between 0 and 1
	printf("Your desired brightness: %f\n",brightness_pct);
	
	int i;
	
	wiringPiSetup();					// init	
	
	for(i = 0; i < num_pins; i++) { 
		
		pinMode(pin_row[i], OUTPUT);
	
	}

	while(1) {
		pwm(brightness_pct, BLINK_PERIOD_MS, pin_row, num_pins);
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
}

