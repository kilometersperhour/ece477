#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int init(void);

int main(int argc, char *argv[]){
	// Used for temporary storage of data
	char *buffer[100];
	// Used as file descriptor through serial
	int serial;

	FILE *s_in, *s_out;
	FILE *disk = NULL;
	serial = init();



	while(fgets(buf, 100, s_in)){
		printf("%s\n", buffer);
	}

}

//Serial port initialization with baud rate
int init(){
	
}
