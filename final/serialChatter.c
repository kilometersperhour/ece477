
#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

//GPIO Pins 20 and 23 for reset and play
#define PIN_RESET 20
#define PIN_GAME 23
/*
int deviceSetup(){
	wiringPiSetup();
	// Setup inputs for the button boys
	for(int i; i <= NUM_BUTTONS; i++){
		pinMode(button[i], INPUT);
	}
	serialPortInit(); // Serial port setup
	wiringPiISR(PIN_RESET, INT_EDGE_RISING, &letgo_reset); // interrupt handlers
	wiringPiISR(PIN_GAME, INT_EDGE_RISING, &letgo_game);
}*/

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
