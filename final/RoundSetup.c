#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

void roundSetup(int reset) {
    if (reset == 1) {
        static uint16_t state = 0;
    }
    char serialBuffer[15] = {0};

    for (int i = 0; i < 15; i++) {
        if ((state >> i) & 1 == 0) { // only compare i-th bit of state for any i
            sprintf(serialBuffer, "atc0=(%d,5,5,5)", i); // white pixel command string
        } else {
            sprintf(serialBuffer, "atc0=(%d,5,0,0)", i); // red pixel command string
        }
	serialChatter(serialBuffer) // send off formatted string with serialPuts
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
