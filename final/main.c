//////////////////////////////////////////////////////////////////
//								//
//		"Knockout Game (Bidirectional)"			//
//	Final Project for ECE 477 - Spring 2021 UMaine		//
//		by Miles M, Jesse P, Travis N			//	
//								//
//////////////////////////////////////////////////////////////////

#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>

void deviceSetup();
void letgo_play();
void letgo_reset();

int livingCheck();
void roundPlay();
void roundSetup(int reset);
void serialChatter();
void youDied();


int direction = 1;

deviceSetup();


int main(){

	

}
