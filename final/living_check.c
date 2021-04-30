livingCheck(){
	// Look mom, Im alive
	int life_status = 1;
	int i;
	last_cursor_loc = //TODO Serial for current location
	//TODO NEED state to be defined

	Do{
		if(state[i] == last_cursor_loc){
			// You have died and so has my faith in you
			life_status = 0;
			return 0;
		}
		i++;
	}
	// Check if you still have a will to live
	while((life_status == 1) && (state[i] != 16)){
		return 1;
	}
}
