struct Pair{                                                //keep data points grouped
    int time;
    int value;
};

struct Pair samples[1000];                                  //1000 samples per second, for a second
struct Pair sample(int t, int v, struct Pair pair); 

while(1) { 
    time_prev, time_now, start_time = getCurrentTime;

    while(time_now < start_time + 1000ms) {                 //while time between 0-1s, sample
        time_now = getCurrentTime;                          //constantly check time

        if(time_now >= time_prev + 1ms) {                   //if a millisecond has passed
            sample(time_now, digitalRead(PIN));             //takes a snapshot
            time_prev = time_now;                           //remember last sample time
        }
    }
    
    struct Pair sample(int t, int v, struct Pair pair) {
        pair.time = t;
        pair.value = v;
        return pair;
    }

    system("avrdude")
}