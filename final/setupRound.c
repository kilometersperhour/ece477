#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

void setupRound(int reset) {
    if (reset == 1) {
        static uint16_t state = 0; // If reset was pressed, set state equal to 0
    }
    char serialBuffer[15] = {0};

    for (int i = 0; i < 15; i++) {
        if ((state >> i) & 1 == 0) { // if i-th bit of state is 0, 
            sprintf(serialBuffer, "atc0=(%d,5,5,5)", i); // set i-th pixel as white
        } else {
            sprintf(serialBuffer, "atc0=(%d,5,0,0)", i); // else set i-th pixel as red
        }
	serialChatter(serialBuffer) // send off formatted string with serialPuts
    }
}
