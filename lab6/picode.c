//Designed to open serial port, set initial settings (including baud rate),
//start when string, "START" is received and store values to rail_voltages.dat

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>

char buf[50];
int char_count;
int rv;

int main(){
	
	//Open serial port 0 with baud rate of 9600
	int fd = serialOpen("/dev/serial0", 9600); //fd is file descriptor

	//TODO want a timer/delay before dumping data (how long?) Consult team
	
	//Cleanup data received from sp0 AKA dumps ALL data
	serialFlush(fd);

	//sends string to serial port 0
	serialPuts(fd, "START");
	
	//file rv opens as write only
	rv = open("rail_voltages.dat", O_WRONLY);

	//Error handling if serial or writing to rails_voltages.dat fails
	if(fd < 0){
		printf("ERROR: fd below 0, cannot open\n\n");
		return -1;
	}
	if(rv < 0)
		printf("ERROR: failed to write to rails_voltages.dat\n\n");

	while(1){
		
		//returns serialport0's number of characters available for reading
		char_count = serialDataAvail(fd);
		
		for(int i=0; i < char_count; i++){
			//grabs next character on serialport0 if it exists, will wait up to 10 seconds if no data is available
			buf[i] = serialGetchar(fd);
		}
		
		//Write to buffer array to rail_voltages.dat
		write(rv, buf, char_count);
		
		//delay 1 second to account for writing function from unistd.h library
		usleep(1000000);
	}
	//cleanup data from sp0
	serialFlush(fd);

	//Close files
	close(rv);
	close(fd);
}
