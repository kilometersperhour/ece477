void livingCheck(){
	// Takes input from main.c and checks if you landed on red or white pixel
	int life_status = 1;

	// Landed on a red pixel, change life_status to zero and end game
	if((state | green) == state){
		life_status = 0;
		return 0;
	}
	// Landed on a white pixel, exit function 
	return 1;
}
