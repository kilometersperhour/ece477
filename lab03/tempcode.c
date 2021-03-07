
//if load is greater than 1 and next is not then set that last pin to be equal to the percent brightness of the load
//divs array load_diff factor_of_divs
//send it a single pin pin_row[i]

for(int i = 0; i <= 7; i++){			//Runs 8 times for 8 pins
	if(divs_array[i] > load_diff[i]){ 	//If the factor_of_divs is negative, grab the last pins factor and set that brightness to the pin
		pwm((divs_array[i-1]/load_diff[i-1]), 1, pinrow[i-1]);	//1ms to update LEDS "instantly" (very quickly)
		i = 0;
		delay(2000);			//Wait 2 seconds

	} else if((divs_array[i] > load_diff[i]) && (i == 0)){		//Seg fault protection if pin0 has greater smaller load than divs_array
		delay(2000);			
	} else {
		pwm((1, 1, pinrow[i]);					//Else set pin value to 1
	}
}
