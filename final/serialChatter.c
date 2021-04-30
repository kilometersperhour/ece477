
#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

// GPIO Pins 20 and 23 for reset and play
// GPIO 20 and 23 for reset and play (in that order)
#define PIN_RESET 28
#define PIN_GAME 4
#define NUM_BUTTONS 2

int deviceSetup(){
	int buttons[2] = {PIN_RESET, PIN_GAME}; 
	wiringPiSetup();
	// Setup inputs for the button boys
	for(int i; i <= NUM_BUTTONS; i++){
		pinMode(buttons[i], INPUT);
	}
	serialPortInit(); // Serial port setup
	wiringPiISR(PIN_RESET, INT_EDGE_RISING, &letgo_reset); // interrupt handlers
	wiringPiISR(PIN_GAME, INT_EDGE_RISING, &letgo_game);
}

int main() {
	
	char commands[5][25] = {
				"if",
				"this",
				"then",
				"that",
				"!"
			       }; 

	for (int i = 0; i < 5; i++) {
		printf(commands[i]);
	}

}
/*
void serialChatter(char string) {

	printf("Sending \'%s\'...", string);
	
	while (serialDataAvail(fd))
	{
		serialGetchar(fd);
		fflush (stdout) ;
	}
	
	serialPuts(fd, string);

	printf("Received \'%s\'in response.");

}*/
