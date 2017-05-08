/******************************************************************************************/
/*                                        STROBE                                          */
/*                                                                                        */
/*  This program is coding for the STROBE Tech Thesis Project.                            */
/*  This program runs on the PIC18F87K90 on the C18 Compiler.                             */
/*  The micro runs at 64MHz with extended instruction set disabled.                       */
/*                                                                                        */
/*  The STROBE is a RGB LED controller with motion sensor detection for reactive lights.  */
/*  There are built-in and user-programmable RGB LED lighting modes for alternate         */
/*  operation.                                                                            */
/*                                                                                        */
/*  Written by: Zachary Lang                                                              */
/*  Electronic Systems Engineering Technology                                             */
/*  Saskatchewn Polytechnic                                                               */
/*  September 2014 - February 2015                                                        */
/******************************************************************************************/

#include "p18f87k90.h"
#include "micro_setup.h"
#include "my_definitions.h"
#include "my_prototypes.h"
#include "menus.h"
#include <string.h>
#include "interrupts.h"

// Main Code //

#pragma code						// ORG for main program.
void main(void)
{	

//*****************  200 Hz Lights Flashing Speed, 1% Duty Cycle  ************************//

	// Frequency - Actual Frequency * 12 //
	// These variables govern the frequency the lights flash at.  They are used to load
	// the high and low Timer0 registers. This function cycles through the twelve light zones
	// turning them off one at a time to reduce noise, hence Actual Frequency * 12.  
	// Timer0 is Fosc(64MHz) / 4 / 8(prescale) = 2000000.
	// Value = 2^16 - (2 000 000 / (Actual Frequency * 12))
	frequency_high = 0xFC;		// 64702 = 2400Hz.
	frequency_low = 0xBE;

	// Duty Cycle - Actual Frequency * 100 //
	// These variables govern the duty cycle divisions of the lights. The Strobe is designed
	// for 1% duty cycle increments.  These values are used to load the high and low
	// Timer1 registers.
	// Timer1 is Fosc(64Mhz) /4 / 8(prescale) = 2000000.
	// Value = 2^16 - (2 000 000 / (Actual Frequency * 100))
	dutycycle_high = 0xFF;		// 65436 = 20000Hz.
	dutycycle_low = 0x9C;

	fade_speed = fade_fast;

//****************************************************************************************//

	// Initializations   //
	// initializations.c //
	osc_init();	
	port_init();
	int_init();
	spi_init();
	oled_init();
	
	// Main Program Loop //
	while(1) {
		
		// OLED Control //
		// oled.c       //
		// Checks the oled_menu var to see which screen is supposed to be showing. If it
		// has changed it will reload the buffer with the new screen. Then it will send
		// the new screen out one byte at a time returning to the main loop between
		// sends until the OLED is ready for another character. When the new screen has
		// finished the function will clear oled_changed var and wait until there is a
		// change.
		strobe_oled();

		// Button Control //
		// buttons.c      //
		// Checks the buttons every 100ms with a 5-cycle 20ms debounce checker in between.
		// The button needs to be pressed for >2 of the 5-cycle checks. If a button is
		// pressed the active menu will be changed based on the current menu and saved
		// to oled_menu var. Button presses will then be ignored for 400ms to avoid
		// erroneous button repeats. Button priority is MENU > ENTER > UP > DOWN.
		strobe_buttons();

		// Lights Control //
		// lights.c		  //
		// Pulse width modulates the LED lights.  The light zones are turned off at one
		// at a time in a repeating cycle so that they all follow the frequency governed
		// by the frequency_low and frequency_high vars. The individual lights have their
		// brightness controlled by turning them on at different intervals after they
		// are turned off. Every off to off time of a single zone is divided into 100
		// sections and the sooner they are turned on after being turned off, the brighter
		// that light zone will be.  The brightness of each zone is controlled by
		// zone_brightness_buffer[13] with maximum brightness being 100 and minimum brightness
		// being 0.
		strobe_lights();

		// Motion Sensor Control //
		// motionsensors.c       //
		strobe_motionsensors();
		


	}


}




// Function definitions //
#include "initializations.c"
#include "interrupts.c"
#include "oled.c"
#include "buttons.c"
#include "lights.c"
#include "motionsensors.c"
#include "adc.c"