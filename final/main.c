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

letgo_reset() {
	static int last_reset_press = 0; // debounce
	if ((last_reset_press + 32) >= millis()) { // valid press detected; not bounce
		roundSetup(1);
	}
	last_reset_press = millis();
}

letgo_play() {
    	static int last_play_press = 0; // debounce
	if ((last_play_press + 32) >= millis()) { // valid press detected; not bounce
		// save new status of cursor
		livingCheck(); //
		direction *= -1; // change direction of gameplay
	}
	last_play_press = millis();

}
