/*
 * serialTest.c:
 *	Very simple program to test the serial port. Expects
 *	the port to be looped back to itself
 *
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
  int wait_this_long;
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

  for (count = 0 ; count != 255 ; )
  {
    if (millis () > nextTime)
    {
      sprintf(serialCmd, "atc1=(0,15,%d,%d,%d)\n",count%255,count%128,count%64);
      printf ("\nOutput: %s: ", serialCmd) ;
      fflush (stdin) ;
      //serialPutchar (fd, count) ;
      serialPuts (fd, serialCmd) ;
      wait_this_long -= 1;
      nextTime += wait_this_long ;
      count += 21;
    }
/*    if (millis() == 1) {
      return 0;
   }
*/ 
    delay (3) ;

    while (serialDataAvail (fd))
    {
      printf (" -> %c", serialGetchar (fd)) ;
      fflush (stdout) ;
    }
  }

  printf ("\n") ;
  return 0 ;
}
