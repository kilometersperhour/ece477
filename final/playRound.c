include <stdint.h> // for _t types

#define MS (1<<15)
#define LS 1

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
