//////////////////////////////////////////////////////////////////
//								//
//		"Knockout Game (Bidirectional)"			//
//	Final Project for ECE 477 - Spring 2021 UMaine		//
//		by Miles M, Jesse P, Travis N			//	
//								//
//////////////////////////////////////////////////////////////////

#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>
#include <stdint.h> // for _t types
#include <stdio.h>
#include <errno.h>
#include <string.h>

// constants for determining when cursor is at "edge" (15<->0 boundary)
#define MS (1<<15)
#define LS 1

// GPIO Pins 20 and 23 for reset and play
#define PIN_RESET 20
#define PIN_GAME 23

int serialPortInit(int fd);
int deviceSetup(int fd);
void letgo_play();
void letgo_reset();

int livingCheck();
void playRound();
void setupRound(int reset);
void serialChatter(int fd, char string, int wait_ms);
void youDied();

int fd = 0;
int direction = 1;
int begin = 0;	// begin gets set to 1 in letgo_reset()


int main(){	
	while(begin != 1);	// once reset has been pressed, begin the game
	while(1) {
		setupRound(0);	// first set the white and red pixels
		playRound();	// have green cursor rotating around, waiting for letgo_play()
				// button press to trigger a livingCheck()
	}
}

int deviceSetup(int fd){

	if ((fd = serialOpen("/dev/ttyUSB0", 115200)) < 0)
	{
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
		printf("Unsuccessful serial connection!");
		return 1;
	} else 
	{ 
		printf("Successful serial connection!");
	}
	
	if (wiringPiSetup() == -1)
	{
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		printf("Unsuccessful wiringPi init!");
		return 1;
	} 
	else 
	{ 
		printf("Successful wiringPi init!");
	}

	// Setup inputs for the button boys
	for(int i; i <= NUM_BUTTONS; i++){
		pinMode(button[i], INPUT);
	}

	// Configure interrupts
	wiringPiISR(PIN_RESET, INT_EDGE_RISING, &letgo_reset);
	wiringPiISR(PIN_GAME, INT_EDGE_RISING, &letgo_game);
	
	// Serial port setup
	fd = serialPortInit(fd); // Serial port setup
	// additional init/setup functions here
	return fd;
}

void letgo_reset() {
	static int last_reset_press = 0; // debounce
	if ((last_reset_press + 32) >= millis()) { // valid press detected; not bounce
		setupRound(1);
	}
	last_reset_press = millis();
	begin = 1;
}

void letgo_play() {
	static int last_play_press = 0; // debounce
	if ((last_play_press + 32) >= millis()) { // valid press detected; not bounce
		// save new status of cursor
		livingCheck(); //
		direction *= -1; // change direction of gameplay
	}
	last_play_press = millis();

}

int livingCheck(){
	// Takes input from main.c and checks if you landed on red or white pixel
	int life_status = 1; // alive.

	// Landed on a red pixel, change life_status to zero and end game
	if((state | cursor) == state){
		life_status = 0; // dead.
		return 0;
	}
	// Landed on a white pixel, exit function 
	return 1;
}


void playRound() {

	static uint16_t cursor = 1;

	static int direction = 1;

	while(livingCheck()) {
		if(0 < direction) {
			//if the direction is 1 (going right to left) and 
			//the current state isn't LS, shift left LED by 
			//one. If it is LS, wrap around to MS
			cursor = (cursor == MS)? LS: cursor << 1; 
		}
		else {
			//if the direction is not 1 (going left to right)
			//and the current state isn't RS, shift right LED by 
			//one. If it is MS, wrap around to LS
			cursor = (cursor == LS)? MS: cursor >> 1;
		}
	}

	return;
}


void setupRound(int reset) {
	if (reset == 1) {
		static uint16_t state = 0; // If reset was pressed, set state equal to 0
    	}
	char serialBuffer[15] = {0};

	for (int i = 0; i < 15; i++) {
		if ((state >> i) & 1 == 0) { // if i-th bit of state is 0, 
			sprintf(serialBuffer, "atc0=(%d,5,5,5)", i); // set i-th pixel as white
		} else {
			sprintf(serialBuffer, "atc0=(%d,5,0,0)", i); // else set i-th pixel as red
		}
		serialChatter(serialBuffer) // send off formatted string with serialPuts
	}
}

void serialChatter(int fd, char * string, int wait_ms) {

//	int wait_until = millis() + wait_ms;
	char response;
	
//	printf("%d\n",fd);

	serialPuts(fd, string); // this really seems like it should be before getchar. 
	printf("Sending %s\n", string);
	fflush(stdin);
//	
//	while (wait_until > millis()); // do nothing until it's time to draw again
	while (serialDataAvail(fd))
	{
		response = serialGetchar(fd);
		fflush (stdout) ;
	}	


	printf("Response\n", response);

}


void youDied() {
	serialChatter(fd, "at10=(5,0,0,4)", roundSpeed); // Play red death animation
	serialChatter(fd, "at10=(0,0,0,8)", roundSpeed); // Fade to black
	return;
}
