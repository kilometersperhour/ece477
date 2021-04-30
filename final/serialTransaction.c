/*
 * speedTest.c:
 *	Less simple program to horribly abuse the serial port. 
 * 	Expects nothing from you or your kind
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int fd ;
  int count ;
  int wait_this_long = 35; // these are like milliseconds sorta
  int subcount = 0;
  int wait = 0;
  char serialCmd[22];
  unsigned int nextTime ;

  if ((fd = serialOpen ("/dev/ttyUSB0", 115200)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  nextTime = millis () + 1000 ;

  for (count = 0 ; count >= 0 ; ) //TODO: come back and make this not 256
  {
    if (millis () > nextTime)
    {
      sprintf(serialCmd, "atc0=(%d,%d,%d,%d)\n",abs((-subcount+1-16) % 16),0,255,0);
      printf ("\nTop out: %s: ", serialCmd) ;
      fflush (stdin) ;
      serialPuts (fd, serialCmd) ;
      wait = millis() + 50;
      while(wait < millis());
      sprintf(serialCmd, "atc0=(%d,%d,%d,%d)\n",abs((-subcount % 16)),255,255,255);
      printf ("\nBot out: %s: ", serialCmd) ;
      fflush (stdin) ;
      //serialPutchar (fd, count) ;
      serialPuts (fd, serialCmd) ;
      delay(50);
      subcount += 1;
      if (subcount == 48) {
        wait_this_long -= 1;
	subcount = 0;
      }
      nextTime += wait_this_long ;
      ++count;
    }
/*    if (millis() == 1) {
      return 0;
   }
*/ 
    delay (3) ;

    while (serialDataAvail (fd))
    {
      printf (" -> %c, wait_this_long is %d", serialGetchar(fd), wait_this_long) ;
      fflush (stdout) ;
    }
  }

  printf ("\n") ;
  return 0 ;
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
