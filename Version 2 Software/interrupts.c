
// Interrupts //

// This code controls the interrupts.

// Interrupt definitions //

#pragma interrupt high_interrupt_routine
void high_interrupt_routine(void)
{
	if (frequency_timer_flag) {

		TMR0H = frequency_high;		// 64702 = 200Hz.
		TMR0L = frequency_low;
		frequency_timer_flag = 0;
		frequency_trigger = 1;
	}

	if (dutycycle_timer_flag) {
		
		TMR1H = dutycycle_high;		// Set for . (96 cycles)
		TMR1L = dutycycle_low;
		dutycycle_timer_flag = 0;
		dutycycle_trigger = 1;
	}
}

#pragma interrupt low_interrupt_routine
void low_interrupt_routine(void)
{
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
		// Turn on the button timer and set it for 20ms.	
		TMR5H = 0x63;
		TMR5L = 0xC0;

		if (button_wait > 0) {
			button_wait--;
		}
		button_timer_flag = 0;
	}		
}

