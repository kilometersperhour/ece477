#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

int serialPortInit(int fd) {

	if ((fd = serialOpen("/dev/ttyUSB0", 115200)) < 0)
	{
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
		printf("Unsuccessful serial connection!\n");
		return 1;
	} else 
	{ 
		printf("Successful serial connection!\n");
	}
	
	if (wiringPiSetup() == -1)
	{
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		printf("Unsuccessful wiringPi init!\n");
		return 1;
	} 
	else 
	{ 
		printf("Successful wiringPi init!\n");
	}

	return fd;
} 

int deviceSetup(int fd) { // passing pointers would be really neat here
	fd = serialPortInit(fd); // Serial port setup
	// additional init/setup functions here
	return fd;
}


void serialChatter(int fd, char * string, int wait_ms) {

	int wait_until = millis() + wait_ms;
	char response;
	
//	printf("%d\n",fd);

	serialPuts(fd, string); // this really seems like it should be before getchar. 
	printf("Sending %s\n", string);
	fflush(stdin);
//	
//	while (wait_until > millis()); // do nothing until it's time to draw again
	while (serialDataAvail(fd))
	{
		response = serialGetchar(fd);
		fflush (stdout) ;
	}	


	printf("Received\n", response);

}

int main() {
	
	int fd = 0;

	fd = deviceSetup(fd);
	
	char commands[5][25] = {
				"atc1=(0,15,5,5,5)",
				"atc0=(0,0,0,0)",
				"atc0=(4,5,5,0)",
				"atc0=(8,5,0,5)",
				"atc0=(12,0,5,5)"
			       }; 
	while(1) {
		for (int i = 0; i < 5; i++) {
			serialChatter(fd, commands[i], 35);
			delay(1000);
		}
	}
}

