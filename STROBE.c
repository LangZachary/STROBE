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
/*  September 2014 - April 2015                                                           */
/******************************************************************************************/

#include "memory.h"
#include "p18f87k90.h"
#include "micro_setup.h"
#include "my_definitions.h"
#include "my_prototypes.h"
#include "menus.h"
#include "dials.h"
#include <string.h>


// High Interrupt //
#pragma code high_vector=0x08		// ORG 08 which is where the high priority
void high_interrupt()				// interrupts are executed.
{									
	_asm GOTO high_interrupt_routine _endasm
}

// Low Interupt //
#pragma code low_vector=0x18		// ORG 18 which is where low priority
void low_interrupt()				// interrupts are executed.
{
	_asm GOTO low_interrupt_routine _endasm
}

// Main Code //
#pragma code maincode						// ORG for main program.
void main(void)
{	

	// Variables
	static unsigned char process_cycle = 1;

//*****************  200 Hz Lights Flashing Speed, 1% Duty Cycle  ************************//

	// Frequency - Actual Frequency * 12 //
	// These variables govern the frequency the lights flash at.  They are used to load
	// the high and low Timer0 registers. This function cycles through the twelve light zones
	// turning them off one at a time to reduce noise, hence Actual Frequency * 12.  
	// Timer0 is Fosc(64MHz) / 4 / 8(prescale) = 2000000.
	// Value = 2^16 - (2 000 000 / (Actual Frequency * 12))
	frequency_high = 0xED;		// 64702 = 2400Hz.
	frequency_low = 0x40;

	// Duty Cycle - Actual Frequency * 100 //
	// These variables govern the duty cycle divisions of the lights. The Strobe is designed
	// for 1% duty cycle increments.  These values are used to load the high and low
	// Timer1 registers.
	// Timer1 is Fosc(64Mhz) /4 / 8(prescale) = 2000000.
	// Value = 2^16 - (2 000 000 / (Actual Frequency * 100))
	dutycycle_high = 0xEE;		// 65436 = 20000Hz.
	dutycycle_low = 0x20;

//****************************************************************************************//

	// Initializations   //
	// initializations.c //
	osc_init();	
	port_init();
	int_init();
	spi_init();
	oled_init();
	adc_init();

	// Welcome Menu Start Up Routine //
	strobe_welcome();



	// Main Program Loop //
	while(1) {
	
		// High Priority Tasks //
		// These tasks are ran once for each loop while low priority tasks are cycled
		// between for each loop.
	
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
		strobe_lights(led_run);

		// Low Priority Tasks //
		// These tasks are cycled through each time the main program loop executes so only
		// one is executed each loop.

		switch (process_cycle) {

			case 1:
					// OLED Control //
					// oled.c       //
					// Checks the oled_menu var to see which screen is supposed to be showing. If it
					// has changed it will reload the buffer with the new screen. Then it will send
					// the new screen out one byte at a time returning to the main loop between
					// sends until the OLED is ready for another character. When the new screen has
					// finished the function will clear oled_changed var and wait until there is a
					// change.
					strobe_oled(oled_run, 0, 0);
					process_cycle++;
					break;

			case 2:
					// Button Control //		// Buttons with action 90+us //
					// buttons.c      //
					// Checks the buttons every 100ms with a 5-cycle 20ms debounce checker in between.
					// The button needs to be pressed for >2 of the 5-cycle checks. If a button is
					// pressed the active menu will be changed based on the current menu and saved
					// to oled_menu var. Button presses will then be ignored for 400ms to avoid
					// erroneous button repeats. Button priority is MENU > ENTER > UP > DOWN.
					strobe_buttons();
					process_cycle++;
					break;

			case 3:
					// Motion Sensor Check //
					// motionsensors.c     //
					// The motion sensors are analyzed. No changes to the lights occur at this time. 
					// This step cross checks the current state of the motion sensors to the previous 
					// state to decide where the tracked targets are located.
					strobe_motionsensors(ms_check);
					process_cycle++;
					break;

			case 4:
					// Motion Sensor Action //
					// motionsensors.c      //
					// If the motion sensors have detected new movement the lights are changed to reflect
					// this. For every zone in zone_active[] that is set, that light has its brightness changed
					// to 100% and the adjacent ones are brightened according to adjacent_brightness,
					// adjacent2_brightness and adjacent3_brightnesws in my_definitions.
					strobe_motionsensors(ms_action);
					process_cycle++;
					break;	
	
			case 5:
					// ADC Control - Both Dials //
					// adc.c       //
					// When the ADC is enabled this function will cycle through checking the two pots on the
			 		// control pad every 40ms.  Each pot is then checked once every 80ms.  The value of the
			 		// pots is saved as a percentage from 1 to 100 in the registers pot1 for the left pot
			 		// and pot2 for the right pot.
					// Only runs if adc_dual_enable is set.
					strobe_adc(adc_dual_run);
					process_cycle++;
					break;

			case 6:
					// ADC Control - Right Dial Only //
					// adc.c       //
					// When the ADC is enabled this function will cycle through checking the right pot on the
			 		// control pad every 40ms.  Each pot is then checked once every 80ms.  The value of the
			 		// pots is saved as a percentage from 1 to 100 in the registers pot1 for the left pot
			 		// and pot2 for the right pot.
					// Only runs if adc_single_enable is set.
					strobe_adc(adc_single_run);
					process_cycle++;
					break;

			case 7:
					// Blinking Control //
					// blink.c			//
					// When a menu item is selected this function causes it to blink so the user knows it is
					// selected. The blinking rate is off for 250ms, on for 500ms.  When the menu item is no
					// longer selected, this function will immediately turn the menu item on and disable
					// further blinking.
					strobe_blink(blink_run);
					process_cycle = 1;
					break;
			
			default:
					// Account for undesirable operation.
					process_cycle = 1;
					break;
		}	
	}
}

// Function definitions //
#include "initializations.c"
#include "interrupts.c"
#include "oled.c"
#include "buttons.c"

#include "motionsensors.c"
#include "adc.c"
#include "blink.c"
#include "dials.c"
#include "mem.c"
#include "welcome.c"
#include "lights.c"

