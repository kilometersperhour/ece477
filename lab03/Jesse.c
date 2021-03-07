//#include "pwm_uniform.h"
#include <sys/types.h> // is this needed for fork()?
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main(void) {

    const float divs_array[8] = { // an array of divisors
        4./255,  // Where each increasing LED must light up when the load doubles,
        8./255,  // each value of this array doubles in kind.
        16./255,  // The values have been multiplied by a factor of four
        32./255,  // because the max load is 4/4.
        64./255, // The values are divided by 255 to normalize them
        128./255, // 255 is the sum of 2^0 through 2^7, representing the
        256./255, // corresponding weights of each LED's brightness.
        512./255
    };

    float load_dif[8];
    int i;
    int j;

    for(i=0; i<8; i++) {
        if(i==0) {
            load_dif[0] = 3.37 - divs_array[0];           //Takes input to calculate first value in load_dif
        }
        else {
            load_dif[i] = load_dif[i-1] - divs_array[i];    //Uses previous load_dif value to calculate current value
        }
    }
    

    for(j=0; j<8; j++) {
        printf("%f \n", load_dif[j]);
    }
    return 0;
}