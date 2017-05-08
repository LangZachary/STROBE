// STROBE
//
// This program is coding for the STROBE Tech Thesis Project.
// For use with the PIC18F87K90 microcontroller.
//
// Written by Zachary Lang
// January 8, 2015

#include <p18f87k90.h>
#include "micro_setup.h"
#include "my_definitions.h"
#include "my_prototypes.h"


#include <delays.h>
#include <timers.h>
#include <spi.h>
#include <string.h>

// High Interrupt //

#pragma code high_vector=0x08		// ORG 08 which is where the high priority
void high_interrupt()				// interrupts are executed.
{									
	high_interrupt_routine();
}

// Low Interupt //

#pragma code low_vector=0x18		// ORG 18 which is where low priority
void low_interrupt()				// interrupts are executed.
{
	low_interrupt_routine();
}

// Main Code //

#pragma code						// ORG for main program.
void main(void)
{	
	// Initializations //
	osc_init();	
	port_init();
	int_init();
	spi_init();
	oled_init();
	
	// Main Program Loop //
	while(1) {
		
		strobe_oled();
		strobe_buttons();

		
/*		if (RED_LED_BRIGHT_COUNT == 0){ 		// When the duty cycle count is reached
			RED_LED = 1; 						// turn on the red LED.
		}
		if (YELLOW_LED_BRIGHT_COUNT == 0){ 		// When the duty cycle count is reached
			YELLOW_LED = 0;						// turn on the yellow LED.
		}
		if (RED_RGB_LED_BRIGHT_COUNT == 0){ 	// When the duty cycle count is reached
			RED_RGB_LED = 0;					// turn on the yellow LED.
		}
		if (GREEN_RGB_LED_BRIGHT_COUNT == 0){ 	// When the duty cycle count is reached
			GREEN_RGB_LED = 0;				  	// turn on the yellow LED.
		}
		if (BLUE_RGB_LED_BRIGHT_COUNT == 0){ 	// When the duty cycle count is reached
			BLUE_RGB_LED = 0;				  	// turn on the yellow LED.
		}*/


	}
}

// Function definitions //
#include "initializations.c"
#include "interrupts.c"
#include "oled.c"
#include "buttons.c"
