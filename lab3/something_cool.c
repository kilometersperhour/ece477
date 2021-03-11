//#include "pwm_gaugelike.h"
#include <sys/types.h> // is this needed for fork()?
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main(void) {

    const int pin_row[] = { // map GPIO-7 to corresponding wiringPi pins
        30,   // GPIO 0
        31,   // GPIO 1
        8,    // GPIO 2
        9,    // GPIO 3
        7,    // GPIO 4
        21,   // GPIO 5
        22,   // GPIO 6
        11    // GPIO 7
    };
    float stress[] = {1.24, 3.62, 1.98, 0.79, 3.26, 1.23, 1.89, 0.32, 3.82, 4.0};  //Fake values to test
    float history[8] = {0, 0, 0, 0, 0, 0, 0, 0}; 
    int i = 0;

    while(1) { 
//        for(int i = 6; i >= 0; i--) {
//            pwm(history[i], 1, pin_row[i]);    
//        }
        history[7] = stress[i] / 4.;          //Manually set last history index with new stress value
        pwm(history, 1, pin_row);             //Turn on LEDs based on history values

        for(int j = 0; j < 6; j++) {          //Update history array
            history[j] = history[j+1];        //By shifting all values down one
        }
        
        i++;                                  //Testing fake values
        if(i > 9) i = 0;

        for(int x = 0; x < 8; x++) {          //Print History array values
            printf("%f", history[x]);
        }
        delay(5000);
    }
}