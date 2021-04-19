#include <stdio.h>
#include <stlib.h>
#include <fnctl.h>
#include <string.h>
#include <unistd.h>

//Wiring pi Serial port library
#include <wiringSerial.h>

//Character buffer length
char buf[50];

int main(){
	
	//Open serial port 0 with baud rate of 9600
	int fd = serialOpen("/dev/serial0", 9600); //fd is file descriptor

	//TODO want a timer/delay before dumping data
	
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
		//Write to buffer array to rail_voltages.dat
		write(rv, buf, char_count);
	}

	//Close files
	close(rv);
	close(fd);
}
