#include <stdint.h> // for _t types

#DEFINE MS 1000000000000000
#DEFINE LS 0000000000000001

...

uint16_t green 0000000000000001;

static int direction = 1;

while(livingCheck()) {
	if(0 < direction) {
		//if the direction is 1 (going right to left) and 
		//the current state isn't LS, shift left LED by 
		//one. If it is LS, wrap around to MS
	       	green = (green == MS)? LS: green << 1; 
	}
	else {
		//if the direction is not 1 (going left to right)  
		//and the current state isn't RS, shift right LED by 
		//one. If it is MS, wrap around to LS
		green = (green == LS)? MS: green >> 1;
	}
}
