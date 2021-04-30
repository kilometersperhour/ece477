#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

int state[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

extern void roundSetup() {
    
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

extern void youDied() {
    serialWrite(fd, "at10=(5,0,0,4)");
    serialWrite(fd, "at10=(0,0,0,8)");
    for(int i = 0; i < 15; i++) {
        state[i] = 0;
    }
}

void serialWrite(int fildes, char string) {

	printf("Sending \'%s\'...");
	
	while (serialDataAvail(fd))
	{
		serialGetchar(fd);
		fflush (stdout) ;
	}
	
	serialPuts(fildes, string);

	printf("Received \'%s\'in response.");

}