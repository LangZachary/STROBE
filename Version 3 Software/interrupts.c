
// Interrupts //

// This code controls the interrupts.

// Interrupt definitions //

#pragma interrupt high_interrupt_routine
void high_interrupt_routine(void)
{

}

#pragma interrupt low_interrupt_routine
void low_interrupt_routine(void)
{
	if (frequency_timer_flag) {

		TMR0H = frequency_high;		// 64702 = 200Hz.
		TMR0L = frequency_low;
		frequency_timer_flag = 0;
		lights_frequency();
//		frequency_trigger = 1;
	}

	if (dutycycle_timer_flag) {
		
		TMR1H = dutycycle_high;		// Set for . (96 cycles)
		TMR1L = dutycycle_low;
		dutycycle_timer_flag = 0;
		lights_dutycycle();
//		dutycycle_trigger = 1;
	}


	// OLED Timer - Turn off timer.
	//				Oled ready to send another command.
	//				Reset interrupt flag.
	if (oled_timer_flag) {
		oled_timer_flag = 0;
		oled_ready = 1;
		oled_timer = 0;
	}

	// Button Timer - Reset the timer to 20ms.
	//			      Decrement the button check counter.
	//			      Reset interrupt flag.
	if (button_timer_flag) {
		// 20ms.	
		TMR5H = 0x63;
		TMR5L = 0xC0;

		if (button_wait > 0) {
			button_wait--;
		}
		button_timer_flag = 0;
	}	

	// Motion Sensor Timer - Motion Sensors ready to be checked.
	//						 Reset interrupt flag.
	//						 Reset the timer to 20ms.
	//						 Degrement the count, on zero motion sensors are ready.
	if (ms_timer_flag) {
		// 20ms.	
		TMR7H = 0x63;
		TMR7L = 0xC0;

		if (!ms_timer_count) {
			ms_ready = 1;				// Motion sensors ready to be checked.
			ms_timer_count = ms_delay;	// Reset the count. Default (5) 20ms >> 100ms.
		} else {
			ms_timer_count--;
		}
		ms_timer_flag = 0;
	}	

	// ADC Timer - 	Decrement the frequency counter.
	//			   	When counter is zero, flag another adc conversion
	//					and reset the counter.
	//			    Reset interrupt flag.
	if (adc_timer_flag) {

		adc_count--;					// Decrement the counter.

		if (!adc_count) {

			adc_ready = 1;				// Another ADC conversion can be done.
			adc_count = adc_delay;		// Restart the counter.
		}
		adc_timer_flag = 0;				// Clear the interrupt flag.
	}	
/*
	// ADC Coversion Finished
	if (adc_flag) {
	
		adc_flag = 0;					// Reset the flag.
		adc_conversion_done = 1;
	}
*/
}

