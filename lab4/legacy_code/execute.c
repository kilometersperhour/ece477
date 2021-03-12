if (execute) {

	if (current_button[0] && current_button[1]) {
	
		return 0; // end program

	} else if (current_button[0]) {
	
		if (wait_time == 32) {
		
			direction *= -1; // reverse direction

		} else {
		
			wait_time /= 2; // increase refresh rate
		
		}

	} else if (current_button[1]) {
	
		if (wait_time == 1024) {
		
			direction *= -1; // reverse direction

		} else {
		
			delay *= 2; // decrease refresh rate
		
		}
	
	}

} 
