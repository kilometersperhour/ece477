/*
 * serialTest.c:
 *	Very simple program to test the serial port. Expects
 *	the port to be looped back to itself
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int fd ;
  int count ;
  int wait_this_long = 35; // these are like milliseconds sorta
  int subcount = 0; // kind of like a clock divider
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

  for (count = 0; count >= 0; count++) //TODO: come back and make this not 256
  {
    if (millis () > nextTime)
    {
      sprintf(serialCmd, "atc1=(0,15,%d,%d,%d)\n",count*21%256,count*21%128,count%64);
      printf ("\nOutput: %s: ", serialCmd) ;
      fflush (stdin) ;
      //serialPutchar (fd, count) ;
      serialPuts (fd, serialCmd) ;
      subcount += 1; // used as a clock divider of sorts
      if (subcount == 48) {
        wait_this_long -= 1;
	subcount = 0;
      }
      nextTime += wait_this_long ;
    }
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
