//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//			ECE 477 Lab 4
//      Move an LED using pushbuttons and GPIO on RPi 4 4GB
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//	By Miles Martin, Travis Nickerson, & Jesse Perkins

#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wiringPi.h>
#include "shift.h"

#define LS 1<<0  //least significant position, rightmost LED lit up 
#define MS 1<<7  //most significant position, leftmost LED lit up

const int output_pins[8] = { // map GPIO-7 to corresponding wiringPi pins
30,   // GPIO 0
31,   // GPIO 1
8,    // GPIO 2
9,    // GPIO 3
7,    // GPIO 4
21,   // GPIO 5
22,   // GPIO 6
11    // GPIO 7
};

const int input_pins[2] = {
14,   // GPIO 11, button A
1,    // GPIO 18, button B
};

const int num_pins = sizeof(pin_row)/sizeof(pin_row[0]);  // Max times to loop


int main (int argc, char *argv[]) {

	int i;
	uint8_t state = 1;
	unsigned int current_button[2], last_button[2];
	unsigned int execute; 
	unsigned int delay = 1024;
	signed int direction = 1;    // oscillates between 1 and -1
                                     // (getting smaller or bigger)
	
	wiringPiSetup();             // init	
	
	for(i = 0; i < num_pins; i++) { 
		pinMode(output_pins[i], OUTPUT);
	}

	for(i = 0; i < 2; i++) {
		pinMode(input_pins[i], INPUT);
		pullUpDnControl (input_pins[i], PUD_UP);  // enable pull up resistors
	}

	// Travis' section??

	// Jesse's super succinct code :D
	while(1) {

		if(0 < direction) {
			//if the direction is 1 (going right to left) and 
			//the current state isn't LS, shift left LED by 
			//one. If it is LS, wrap around to MS
	        	(state == LS)? state = MS: state << 1; 
		}
		else {
			//if the direction is not 1 (going left to right)  
			//and the current state isn't RS, shift right LED by 
			//one. If it is MS, wrap around to LS
			(state == MS)? state = LS: state >> 1;
		}
	}
}
