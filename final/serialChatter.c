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
		printf("Unsuccessful serial connection!");
		return 1;
	} else 
	{ 
		printf("Successful serial connection!");
	}
	
	if (wiringPiSetup() == -1)
	{
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		printf("Unsuccessful wiringPi init!");
		return 1;
	} 
	else 
	{ 
		printf("Successful wiringPi init!");
	}

	return fd;
} 

int deviceSetup(int fd) { // passing pointers would be really neat here
	fd = serialPortInit(fd); // Serial port setup
	// additional init/setup functions here
	return fd;
}


void serialChatter(int fd, char * string) {

	char response = 0;
	
	printf("%d\n",fd);

//	printf("Sending \'%s\'...\n", string);
	fflush(stdin);

	while (serialDataAvail(fd))
	{
		response = serialGetchar(fd);
		fflush (stdout) ;
	}
	
	serialPuts(fd, string);

//	printf("Received \'%s\'in response.\n");

}

int main() {
	
	int fd = 0;

	fd = deviceSetup(fd);
	
	char commands[5][25] = {
				"atc1=(0,15,5,5,5)\n",
				"atc0=(0,0,0,0)\n",
				"atc0=(4,5,5,0)\n",
				"atc0=(8,5,0,5)\n",
				"atc0=(12,0,5,5)\n"
			       }; 
	while(1) {
		for (int i = 0; i < 5; i++) {
			serialChatter(fd, commands[i]);
			delay(1000);
		}
	}
}

