#include <stdlib.h>

#define LS 1<<0  //least significant position, rightmost LED lit up 
#define MS 1<<7  //most significant position, leftmost LED lit up

main {
    if(0 < direction) {
        (state == LS)? state = MS: state << 1; //if the direction is 1 (going right to left) and 
                                               //the current state isn't LS, shift left LED by 
                                               //one. If it is LS, wrap around to MS
    }
    else {
        (state == MS)? state = LS: state >>1;  //if the direction is not 1 (going left to right)  
                                               //and the current state isn't RS, shift right LED by 
                                               //one. If it is MS, wrap around to LS
    }
}