
// Interrupts //

// This code controls the interrupts.

// Interrupt definitions //

#pragma interrupt high_interrupt_routine
void high_interrupt_routine(void)
{
/*
	// Frequency Timer - Set trigger, another zone is ready to be
	//					 cycled off.
	if (frequency_timer_flag) {

		TMR0H = frequency_high;		// 64702 = 200Hz.
		TMR0L = frequency_low;
		frequency_timer_flag = 0;
		frequency_trigger = 1;
	}

	// Duty Cycle Timer - Set trigger, check zones to see if they
	//					  are ready to be turned off depending on their
	//					  target brightness.
	if (dutycycle_timer_flag) {
		
		TMR1H = dutycycle_high;		// Set for . (96 cycles)
		TMR1L = dutycycle_low;
		dutycycle_timer_flag = 0;
		dutycycle_trigger = 1;
	}
*/
}

#pragma interrupt low_interrupt_routine
void low_interrupt_routine(void)
{

	// Frequency Timer - Set trigger, another zone is ready to be
	//					 cycled off.
	if (frequency_timer_flag) {

		TMR0H = frequency_high;		// 64702 = 200Hz.
		TMR0L = frequency_low;
		frequency_timer_flag = 0;
		frequency_trigger = 1;
		INTCONbits.GIEL = 0;		// Enable low priority interrupts.
	}

	// Duty Cycle Timer - Set trigger, check zones to see if they
	//					  are ready to be turned off depending on their
	//					  target brightness.
	if (dutycycle_timer_flag) {
		
		TMR1H = dutycycle_high;		// Set for . (96 cycles)
		TMR1L = dutycycle_low;
		dutycycle_timer_flag = 0;
		dutycycle_trigger = 1;
		INTCONbits.GIEL = 0;		// Enable low priority interrupts.
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

	// Blink Timer - Decrement the frequency counter.
	//			   	 When counter is zero, flag another blink.
	//			     Reset interrupt flag.
	//				 Counter must be reset in software.
	if (blink_timer_flag) {

		blink_count--;					// Decrement the counter.

		if (!blink_count) {

			blink_ready = 1;			// Another blink can be done.
		}
		blink_timer_flag = 0;			// Clear the interrupt flag.
	}	

}

