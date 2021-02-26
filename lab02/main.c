#include "pwm_uniform.h"
#include <sys/types.h> // is this needed for fork()?
#include <unistd.h>
#include <stdio.h>


#define VISIBLE_THRESHHOLD (float) 25/1000 // 25 Hz / 1000 ms ... 
// not really sure if this is the right approach.
// looking for value to pass to 2nd arg. of pwm (the period)

const int pin_row[] = {22, 26, 23, 27, 24, 28, 29, 25}; 	// WiringPi pin numbers
								// lined up on breadboard 

const int num_pins = sizeof(pin_row)/sizeof(pin_row[0]);	// Max times to loop


int main (int argc, char *argv[]) {
	
	if (255 <= argv[1]) {

		printf("Error: please pass an argument between 0 and 255 in dec, hex, or octal.\n");
		return 0;

	} else {

		int parent = getppid();
		int child = getpid();

		printf("Child process: %d\n",child);
		printf("Parent process: %d\n",parent);

		if (getpid() == getppid()) {

			printf("Parent process ending!\n");
			return 0;

		} else {

			printf("Child process %d still alive\n", child);

		}

	}

	float brightness_pct = argv[1]/255; 
	printf("Your desired brightness: %f\n",brightness_pct);
	
	int i;
	
	wiringPiSetup();					// init
	
	for(i = 0; i < num_pins; i++) {				
		
		pinMode(pin_row[i], OUTPUT);			// set pin_row pins to OUTPUT
	
	}


	while(1) {
	
		for(i = 0; i < 8; i++) {
		
			digitalWrite(pin_row[i], HIGH);		// set pins; turn on lights
			delay(500);
	
		}
	
		for(i = 0; i < 8; i++) {
		
			digitalWrite(pin_row[i], LOW);		// clear pins; turn off lights
			delay(500);
	
		}
	}
	return 0;
}
