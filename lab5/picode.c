#include <sys/time.h>
#include <wiringPi.h>
#include <stdio.h>                                          //included to debug sample collection

#define PIN 0                                            //GPIO 17 = wiring pi 0

struct Pair{                                                //keep data points grouped
    int time;
    int value;
};

struct timeval timeofday;

__uint8_t offset;
__uint8_t direction;

struct Pair samples[1000];                                  //1000 samples per second, for a second

struct Pair sample(int t, int v, struct Pair pair); 
void clock_setter(void);

unsigned long long time_prev, time_now, start_time;

main() {
    clock_setter();


}

void clock_setter(void) {
    char string[81];
    int i;
    float periodsum;
    float frequency;

    while(1) { 
        
	i = 0;
	periodsum = 0;
	frequency = 0;
	
	gettimeofday(&timeofday, NULL);
        
	start_time = (unsigned long long)(timeofday.tv_sec) * 1000 + (unsigned long long)(timeofday.tv_usec) / 1000;
	time_now = start_time;
	time_prev = start_time;

        while(time_now < start_time + 1000) {                   //while time between 0-1s, sample
            gettimeofday(&timeofday, NULL);                     //constantly check time
            time_now = (unsigned long long)(timeofday.tv_sec) * 1000 + (unsigned long long)(timeofday.tv_usec) / 1000; 

            if(time_now >= time_prev + 1) {                     //if a millisecond has passed
                sample(time_now, digitalRead(PIN), samples[i]);             //takes a snapshot
		i++;
                time_prev = time_now;                           //remember last sample time
            }
	
            periodsum += samples[i].time;                             // Sum all the periods together
       
       	}

        frequency = (1/(periodsum/i)); 			// Computes frequency from the averaged period over the 1000ms sample time
	printf("%f\n", frequency);

        sprintf(string, "sudo avrdude -C ~/avrdude_gpio.conf -c pi_1 -p atmega88p -U eeprom:w:%x,%x:m", offset, direction);
       // system(string);
    }
}

struct Pair sample(int t, int v, struct Pair pair) {
    pair.time = t;
    pair.value = v;
    return pair;
}
