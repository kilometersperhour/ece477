// ECE 477 Lab 1 Due 2/19/2021 @ 4pm
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Introduction: Printout the size of data types:
// char, short, int, long, float and double
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Group: Miles Martin, Travis Nickerson, Jesse Perkins

#include <stdio.h>                                              // adds printf()
#include <limits.h>                                             // adds the defines for max length of these variables

printf("A float is %d bits long in decimal", float);            // these are the lengths of different variable types
printf("A double is %d bits long in decimal", double);
printf("A char is %x bits long in hex", char);          
printf("A short is %x bits long in hex", short);
printf("An int is %x bits long in hex", int);
printf("A long is %x bits long in hex", long);
printf("A float is %x bits long in hex", float);
printf("A double is %x bits long in hex", double);

printf("Decimal size of a signed int is %d", INT_MAX);          // decimal size of a signed int
printf("Decimal size of an unsigned int is %d", UINT_MAX);      // decimal size of an unsigned int
printf("Decimal size of a signed long int is %d", LONG_MAX);    // decimal size of a signed long int
printf("Decimal size of an unsigned long int is %d", ULONG_MAX);// decimal size of an unsigned long int

printf("Hex size of a signed int is %x", INT_MAX);              // hex size of a signed int
printf("Hex size of an unsigned int is %x", UINT_MAX);          // hex size of an unsigned int
printf("Hex size of a signed long int is %x", LONG_MAX);        // hex size of a signed long int
printf("Hex size of an unsigned long int is %x", ULONG_MAX);    // hex size of an unsigned long int