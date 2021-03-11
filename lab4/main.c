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

const int num_pins = sizeof(pin_row)/sizeof(pin_row[0]);	// Max times to loop

int main (int argc, char *argv[]) {

	int i;
	
	wiringPiSetup();					// init	
	
	for(i = 0; i < num_pins; i++) { 
		pinMode(pin_row[i], OUTPUT);
	}

	
	pinMode(, OUTPUT);

}

