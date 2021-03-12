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
//#include "shift.h"

#define LS 1<<0  //least significant position, rightmost LED lit up 
#define MS 1<<7  //most significant position, leftmost LED lit up

const int output_pins[8] = { // map wiringPi0-7 to corresponding GPIO pins
0,   // GPIO 17
1,   // GPIO 18
2,   // GPIO 27
3,   // GPIO 22
4,   // GPIO 23
5,   // GPIO 24
6,   // GPIO 25
7    // GPIO 4
};

const int input_pins[2] = {
8,   // GPIO 8, button A
9,   // GPIO 9, button B
};

const int num_inputs = sizeof(input_pins)/sizeof(input_pins[0]);  // Max times to loop
const int num_outputs = sizeof(output_pins)/sizeof(output_pins[0]);  // Max times to loop

int main (int argc, char *argv[]) {
	
	// Miles Martin

	int i;
	unsigned char state = 0x01;
	unsigned int current_button[2] = {0,0};
	unsigned int last_button[2] = {0,0};
	unsigned int execute; 
	unsigned int wait_time = 1024;
	signed int direction = -1;    // oscillates between 1 and -1
                                     // (getting smaller vs. getting bigger)
	const unsigned int debounce_delay = 32; // 32ms 
	int button_a = input_pins[0]; //Button A
	int button_b = input_pins[1]; //Button B
	int exit_flag = 0;
	
	wiringPiSetup();             // pin init, probably?	
	
	for(i = 0; i < num_outputs; i++) { 
		pinMode(output_pins[i], OUTPUT);
	}

	for(i = 0; i < num_inputs; i++) {
		pinMode(input_pins[i], INPUT);
		pullUpDnControl (input_pins[i], PUD_UP);  // enable pull up resistors
	}

	// Travis Nickerson
	while(1) {
		digitalWriteByte(state);

		for(i=0; i<2; i++){
			last_button[i] = current_button[i];  // store the history of the button
			current_button[i] = digitalRead(input_pins[i]);  // get current value of the button
		}

		// Button A debouncing
		if(button_a == 1){
			current_button[0] = 1; 	// Set current value for button A to 1
			delay(debounce_delay);
		} else {
			current_button[0] = 0;	// Reset current value of A to 0
			delay(debounce_delay);
		}
		// Button B debouncing
		if(button_b == 1){
			current_button[1] = 1;	// Set current value for button B to 1
			delay(debounce_delay);
		} else {
			current_button[1] = 0;	// Reset current value of B to 1
			delay(debounce_delay);
		}

		// Exit flag while loop
		while(button_a == 1 || button_b == 1){		// If either button receives a signal
			delay(250);				// 0.25 Second delay to allow both buttons to be pressed and account for bouncing
			if(button_a == 1 && button_b == 1){	// Check if both buttons are pressed
				exit_flag = 1;			// Send exit flag to main program
				printf("Exit!");
			}
		}

		if ((current_button[0] == last_button[0]) && (current_button[1] == last_button[1])) {
			execute = 0;
		} else {
			execute = 1;
		}
	
	
		// Miles Martin
	
		if (execute) {
		
			if (current_button[0] && current_button[1]) {
				return 0; // end program
			} else if (current_button[0]) {
				if (wait_time == 32) {
					direction *= -1; // reverse direction
				} else {
					wait_time /= 2; // increase refresh rate
				}
			} else if (current_button[1]) {
				if (wait_time == 1024) {
					direction *= -1; // reverse direction
				} else {
					wait_time *= 2; // decrease refresh rate
				}
			}
		} 
	
		// Miles Martin
		printf("%d is state; %d is ternary output\n",state, ((state == MS)? LS: state << 1));
		delay(wait_time - debounce_delay);
	
		// Jesse Perkins

		if(0 < direction) {
			//if the direction is 1 (going right to left) and 
			//the current state isn't LS, shift left LED by 
			//one. If it is LS, wrap around to MS
		       	state = (state == MS)? LS: state << 1; 
		}
		else {
			//if the direction is not 1 (going left to right)  
			//and the current state isn't RS, shift right LED by 
			//one. If it is MS, wrap around to LS
			state = (state == LS)? MS: state >> 1;
		}
		
	}
	
	digitalWriteByte((int)state); // turn off all LEDs 

}
