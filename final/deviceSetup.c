//GPIO Pins 20 and 23 for reset and play
#define PIN_RESET 20
#define PIN_GAME 23

int deviceSetup(){
	wiringPisetup();
	// Setup inputs for the button boys
	for(int i; i <= NUM_BUTTONS; i++){
		pinMode(button[i], INPUT);
	}
	// Serial port setup
	wiringPiISR(PIN_RESET, INT_EDGE_RISING, &letgo_reset);
	wiringPiISR(PIN_GAME, INT_EDGE_RISING, &letgo_game);

