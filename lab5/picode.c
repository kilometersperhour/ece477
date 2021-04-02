#include <sys/time.h>
#include <wiringPi.h>
#include <stdio.h>                                          //included to debug sample collection

#define PIN 0                                            //GPIO 17 = wiring pi 0
#define DURATION 1000

struct timeval timeofday;

__uint8_t offset;
__uint8_t direction;

unsigned long long samples_time[DURATION];                                  //1000 samples per second, for a second
__uint8_t samples_value[DURATION];

void clock_setter(void);

unsigned long long start_time, time_now, time_prev;

main() {
    wiringPiSetup();
    clock_setter();


}

void clock_setter(void) {
    char string[81];
    int i,j;
    int edges[DURATION-2];
    int periods[DURATION-3];
    int calibration = 0;
    unsigned long long periodsum;
    double frequency, period;

    while(1) { 
        
	i = 0;
	periodsum = 0;
	frequency = 0;
	
	gettimeofday(&timeofday, NULL);
        
	start_time = ((unsigned long long)(timeofday.tv_sec) * 1000 + (unsigned long long)(timeofday.tv_usec) / 1000);
	time_now = 0;
	time_prev = 0;

        while(time_now < DURATION) {                   //while time between 0-1s, sample
            gettimeofday(&timeofday, NULL);                     //constantly check time
            time_now = ((unsigned long long)(timeofday.tv_sec) * 1000 + (unsigned long long)(timeofday.tv_usec) / 1000)-start_time; 

            if(time_now >= time_prev + 1) {                     //if a millisecond has passed
		samples_time[i] = time_now;                     // take a snapshot
		samples_value[i] = digitalRead(PIN);
	
		i++;
		//printf("i is %d\n",i);
                time_prev = time_now;                           //remember last sample time
            }
	
            periodsum += samples_time[i-1];                             // Sum all the periods together
       
       	}
        
	for (i = 0; i < DURATION - 1; i++) { // find all edges of pulse train
	    if (samples_value[i] != samples_value[i+1]) {
		edges[j] = i; // list of all rising/falling edges' indices in sample_value
		j++;
	    }
	}
	

/*        for (i = 0; i < j-2; i++) { // average all periods of all waves
	    periods[edges[i]] = ((samples_time[i+2] - samples_time[i]) / 2.) + samples_time[i];
	}

	for (i = 0; i < j-2; i++) {
	    periodsum += periods[edges[i]];
	}

        printf("periods[edges[i]] is %d\n",periods[edges[i]]);

	period = periodsum / (j-2);

	frequency = 1. / period;

	if (frequency < 100)  {
	
            calibration--;

	} else if (frequency > 100) {
	
            calibration++;

	}

        printf("period, frequency, calibration: %f, %f. %d\n", period, frequency, calibration);
*/
	
	printf("%llu\n", samples_time[i]);
	
	frequency = (1/(periodsum/(i))); 			// Computes frequency from the averaged period over the 1000ms sample time
	printf("i = %d\n", (i));
	printf("periodsum = %llu\n", periodsum);
	printf("(double)periodsum/(i) = %lf\n", ((double)periodsum/(i)));
	printf("1/((double)periodsum/(i)) = %lf\n", (1/((double)periodsum/(i))));
	printf("f is %lf and i is %d\n\n", frequency, i);
        
        sprintf(string, "sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88p -U eeprom:w:%x,%x:m", offset, direction);
       // system(string);
    }
}
