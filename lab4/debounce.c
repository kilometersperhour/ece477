button_a = input_pins[1] //Button A
button_b = input_pins[2] //Button B

while(1){
	if(button_a == 1){
		current_button[0] = 1; 	// Set current value for button A to 1
		delay(32);
	} else {
		current_button[0] = 0;	// Reset current value of A to 0
		delay(32);
	}
	if(button_b == 1){
		current_button[1] = 1;	// Set current value for button B to 1
		delay(32);
	} else {
		current_button[1] = 0;	// Reset current value of B to 1
		delay(32);
	

