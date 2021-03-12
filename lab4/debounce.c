button_a = input_pins[1] //Button A
button_b = input_pins[2] //Button B
int exit_flag = 0;

while(1){

	// Button A debouncing
	if(button_a == 1){
		current_button[0] = 1; 	// Set current value for button A to 1
		delay(32);
	} else {
		current_button[0] = 0;	// Reset current value of A to 0
		delay(32);
	}
	
	// Button B debouncing
	if(button_b == 1){
		current_button[1] = 1;	// Set current value for button B to 1
		delay(32);
	} else {
		current_button[1] = 0;	// Reset current value of B to 1
		delay(32);
	}

	// Exit flag while loop
	while(button_a == 1 || button_b == 1){		// If either button receives a signal
		delay(250);				// 0.25 Second delay to allow both buttons to be pressed and account for bouncing
		if(button_a == 1 && button_b == 1){	// Check if both buttons are pressed
			exit_flag = 1;			// Send exit flag to main program
		}
	}

}
