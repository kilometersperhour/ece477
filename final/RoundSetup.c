#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

extern void roundSetup() {
    int state[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    /*int redspots = 0;
    for(int i = 0; i<15; i++) {
        if (state[i] == 1)
            redspots++;
    } */
    for(int i = 0; i<15; i++) {
        serial("atc1=(0,15,5,5,5)");
        if(state[i] == 0) {
            serial("atc0=(%d,5,5,5)", i);
        } else {
            serial("atc0=(%d,5,0,0)", i);
        }
    }
}