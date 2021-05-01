//GPIO Pins 20 and 23 for reset and play
#define PIN_RESET 20
#define PIN_GAME 23

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

