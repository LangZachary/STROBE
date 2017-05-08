
// Interrupts //

// This code controls the interrupts.

// Interrupt definitions //

#pragma interrupt high_interrupt_routine
void high_interrupt_routine(void)
{
/*	if (!SWITCH1 && RED_LED_BRIGHTNESS > 1) // If the S1 isn't pressed
	{
		RED_LED_BRIGHTNESS = RED_LED_BRIGHTNESS - 1; // Reduce the red LED duty cycle by 1%. Min 0%
	}
	else if (SWITCH1 && RED_LED_BRIGHTNESS < 99) // If S1 is pressed
	{
		RED_LED_BRIGHTNESS = RED_LED_BRIGHTNESS + 1; // Increase the red LED duty cycle by 1%. Max 100%
	}
	if (!SWITCH2 && YELLOW_LED_BRIGHTNESS > 1) // If the S2 isn't pressed
	{
		YELLOW_LED_BRIGHTNESS = YELLOW_LED_BRIGHTNESS - 1; // Reduce the yellow LED duty cycle by 1%. Min 0%
	}
	else if (SWITCH2 && YELLOW_LED_BRIGHTNESS < 99) // If S2 is pressed
	{
		YELLOW_LED_BRIGHTNESS = YELLOW_LED_BRIGHTNESS + 1; // Increase the yellow LED duty cycle by 1%. Max 100%
	}
	if (!DIP1 && RED_RGB_LED_BRIGHTNESS > 1) // If the S2 isn't pressed
	{
		RED_RGB_LED_BRIGHTNESS = RED_RGB_LED_BRIGHTNESS - 1; // Reduce the yellow LED duty cycle by 1%. Min 0%
	}
	else if (DIP1 && RED_RGB_LED_BRIGHTNESS < 99) // If S2 is pressed
	{
		RED_RGB_LED_BRIGHTNESS = RED_RGB_LED_BRIGHTNESS + 1; // Increase the yellow LED duty cycle by 1%. Max 100%
	}
	if (!DIP2 && GREEN_RGB_LED_BRIGHTNESS > 1) // If the S2 isn't pressed
	{
		GREEN_RGB_LED_BRIGHTNESS = GREEN_RGB_LED_BRIGHTNESS - 1; // Reduce the yellow LED duty cycle by 1%. Min 0%
	}
	else if (DIP2 && GREEN_RGB_LED_BRIGHTNESS < 99) // If S2 is pressed
	{
		GREEN_RGB_LED_BRIGHTNESS = GREEN_RGB_LED_BRIGHTNESS + 1; // Increase the yellow LED duty cycle by 1%. Max 100%
	}
	if (!DIP3 && BLUE_RGB_LED_BRIGHTNESS > 1) // If the S2 isn't pressed
	{
		BLUE_RGB_LED_BRIGHTNESS = BLUE_RGB_LED_BRIGHTNESS - 1; // Reduce the yellow LED duty cycle by 1%. Min 0%
	}
	else if (DIP3 && BLUE_RGB_LED_BRIGHTNESS < 99) // If S2 is pressed
	{
		BLUE_RGB_LED_BRIGHTNESS = BLUE_RGB_LED_BRIGHTNESS + 1; // Increase the yellow LED duty cycle by 1%. Max 100%
	}
	RED_LED_BRIGHT_COUNT = RED_LED_BRIGHTNESS;				// Store the current duty cycle.
	YELLOW_LED_BRIGHT_COUNT = YELLOW_LED_BRIGHTNESS;		// Store the current duty cycle.
	RED_RGB_LED_BRIGHT_COUNT = RED_RGB_LED_BRIGHTNESS;		// Store the current duty cycle.
	GREEN_RGB_LED_BRIGHT_COUNT = GREEN_RGB_LED_BRIGHTNESS;	// Store the current duty cycle.
	BLUE_RGB_LED_BRIGHT_COUNT = BLUE_RGB_LED_BRIGHTNESS;	// Store the current duty cycle.
	YELLOW_LED = 1;			// Turn the yellow LED off.
	RED_LED = 0;			// Turn the red LED off.
	RED_RGB_LED = 1;		// Turn the red RGB off.
	GREEN_RGB_LED = 1;		// Turn the green RGB off.
	BLUE_RGB_LED = 1;		// Turn the blue RGB off.

*/
/*
	RED_LED_BRIGHT_COUNT = RED_LED_BRIGHT_COUNT - 1;
	YELLOW_LED_BRIGHT_COUNT = YELLOW_LED_BRIGHT_COUNT - 1;
	RED_RGB_LED_BRIGHT_COUNT = RED_RGB_LED_BRIGHT_COUNT - 1;
	GREEN_RGB_LED_BRIGHT_COUNT = GREEN_RGB_LED_BRIGHT_COUNT - 1;
	BLUE_RGB_LED_BRIGHT_COUNT = BLUE_RGB_LED_BRIGHT_COUNT - 1;
	TMR1H = 255;			// 200 cycles - 65336
	TMR1L = 56;				// 100us.
	PIR1bits.TMR1IF = 0;	// Clear Timer1 interrupt flag.
*/
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
	// OLED Timer - Reset the timer to 20ms.
	//				Decrement the button check counter.
	//				Reset interrupt flag.
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

