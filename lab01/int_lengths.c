// ECE 477 Lab 1 Due 2/19/2021 @ 4pm
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Introduction: Printout the size of data types:
// char, short, int, long, float and double
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Group: Miles Martin, Travis Nickerson, Jesse Perkins

#include <stdio.h>                                              // adds printf()
#include <limits.h>                                             // adds the defines for max length of these variables

void main() {

    printf("A char is %d bits long in decimal\n", sizeof(char));          
    printf("A short is %d bits long in decimal\n", sizeof(short));
    printf("An int is %d bits long in decimal\n", sizeof(int));
    printf("A long is %d bits long in decimal\n", sizeof(long));
    printf("A float is %d bits long in decimal\n", sizeof(float));            // these are the lengths of different variable types
    printf("A double is %d bits long in decimal\n", sizeof(double));

    printf("A char is %x bits long in hex\n", sizeof(char));          
    printf("A short is %x bits long in hex\n", sizeof(short));
    printf("An int is %x bits long in hex\n", sizeof(int));
    printf("A long is %x bits long in hex\n", sizeof(long));
    printf("A float is %x bits long in hex\n", sizeof(float));
    printf("A double is %x bits long in hex\n", sizeof(double));

    printf("Decimal size of a signed int is %d\n", INT_MAX);          // decimal size of a signed int
    printf("Decimal size of an unsigned int is %u\n", UINT_MAX);      // decimal size of an unsigned int
    printf("Decimal size of a signed long int is %ld\n", LONG_MAX);    // decimal size of a signed long int
    printf("Decimal size of an unsigned long int is %lo\n", ULONG_MAX);// decimal size of an unsigned long int

    printf("Hex size of a signed int is %x\n", INT_MAX);              // hex size of a signed int
    printf("Hex size of an unsigned int is %x\n", UINT_MAX);          // hex size of an unsigned int
    printf("Hex size of a signed long int is %x\n", LONG_MAX);        // hex size of a signed long int
    printf("Hex size of an unsigned long int is %x\n", ULONG_MAX);    // hex size of an unsigned long int

}        