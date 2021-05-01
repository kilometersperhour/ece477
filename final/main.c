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

//GPIO Pins 20 and 23 for reset and play
#define PIN_RESET 20
#define PIN_GAME 23

int serialPortInit(int fd);
int deviceSetup(int fd);
void letgo_play();
void letgo_reset();

int livingCheck();
void roundPlay();
void roundSetup(int reset);
void serialChatter();
void youDied();

int fd = 0;
int direction = 1;
int begin = 0;   // begin gets set to 1 in letgo_reset()

deviceSetup();


int main(){	
	while(begin != 1);   // once reset has been pressed, begin the game
	while(1) {
		roundSetup(0);   // first set the white and red pixels
		roundPlay();     // have green pixel rotating around, waiting for letgo_play()
	}
}

int serialPortInit(int fd) {

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

	return fd;
} 

int deviceSetup(int fd){

	wiringPiSetup();
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

void serialChatter(int fd, char * string) {

	char response = 0;
	
	printf("%d\n",fd);

//	printf("Sending \'%s\'...\n", string);
	fflush(stdin);

	while (serialDataAvail(fd))
	{
		response = serialGetchar(fd);
		fflush (stdout) ;
	}
	
	serialPuts(fd, string);

//	printf("Received \'%s\'in response.\n");

}

letgo_reset() {
	static int last_reset_press = 0; // debounce
	if ((last_reset_press + 32) >= millis()) { // valid press detected; not bounce
		roundSetup(1);
	}
	last_reset_press = millis();
	begin = 1;
}

letgo_play() {
    	static int last_play_press = 0; // debounce
	if ((last_play_press + 32) >= millis()) { // valid press detected; not bounce
		// save new status of cursor
		livingCheck(); //
		direction *= -1; // change direction of gameplay
	}
	last_play_press = millis();

}
