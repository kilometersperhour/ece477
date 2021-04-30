#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

void roundSetup(int reset) {
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

extern void youDied() {
    serialWrite(fd, "at10=(5,0,0,4)"); // Play red death animation
    serialWrite(fd, "at10=(0,0,0,8)"); // Fade to black
}

void serialChatter(char string) {

	printf("Sending \'%s\'...", string);
	
	while (serialDataAvail(fd))
	{
		serialGetchar(fd);
		fflush (stdout) ;
	}
	
	serialPuts(fd, string);

	printf("Received \'%s\'in response.");

}
