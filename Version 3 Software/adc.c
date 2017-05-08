/*************************************************************************************
 *                                    ADC											 *
 *************************************************************************************/

/*  Root function for processing ADC.
 *  When the ADC is enabled this function will cycle through checking the two pots on the
 *  control pad every 40ms.  Each pot is then checked once every 80ms.  The value of the
 *  pots is saved as a percentage from 1 to 100 in the registers dial1 for the left pot
 *  and dial2 for the right pot.  This process will continue until adc_enable is cleared.
 */
void strobe_adc(unsigned char adc_process)
{
	static unsigned char	adc_enable = 0;
	static unsigned char	current_pot = 1;
	static unsigned char	pot1 = 0;
	static unsigned char	pot2 = 0;
	

	// Variable passed into the function decides which process is completed.
	// 1 - Initialization process for starting up the adc unit.
	// 2 - Deinitialization process for stopping the adc unit.
	// 3 - General operation.
	switch (adc_process) {

		// Initialization Process //
		case 1: {

					adc_init();					// Re-initialize the adc.
					Nop();
					pot_level = 0x00;			// Clear the value in the adc register.
					Nop();
					adc_on = 1;					// Turn on the adc module.
					Nop();	
		
					current_pot = 1;			// Clear all the variable registers useed by
					pot1 = 0;					// the adc.
					pot2 = 0;
							
					adc_ready = 0;				// Set up the timer for setting delay
					adc_timer_flag = 0;			// between adc acquisitions.
					adc_count = adc_delay;
					adc_timer = 1;
					adc_enable = 1;				// Turn on adc control in the general adc process.

				} break;

		// Deinitialization Process //
		case 2: {
	
					adc_on = 0;					// Turn off the adc module.
					Nop();
				
					adc_timer = 0;				// Turn off the adc delay timer.
					adc_enable = 0;				// Turn off adc control in the general adc process.	

				} break;

		// General Process //
		case 3: {

					// Check for adc control enabled.
					if (!adc_enable) {
						break;
					}

					// Check for the adc delay.
					if (!adc_ready) {
						break;
					}

					// Check the current pot.
					switch (current_pot) {

						// Pot 1 - current_pot = 1.
						case 1: {

									pot1 = pot_level;		// Read the value from the adc.
									Nop();
									adc_select = adc_pot2;	// Point the adc to pot 2 for conversion.
									Nop();
									current_pot = 2;
									Nop();
									adc_start = 1;			// Start the conversion.
									Nop();
									adc_ready = 0;			// Start delay before read and next conversion.
									
								} break;
				
						// Pot 2 - current_pot = 2.
						case 2: {
	
									pot2 = pot_level;		// Read the value from the adc.
									Nop();
									adc_select = adc_pot1;  // Point the adc to pot 1 for conversion.
									Nop();
									current_pot = 1;
									Nop();
									adc_start = 1;			// Start the conversion.
									Nop();
									adc_ready = 0;			// Start delay before read and next conversion.
	
									strobe_oled(load_adc, pot1, pot2);	// Change the OLED based on the
																		// pot 1, 2.
								} break;

						// Error
						default: {
									current_pot = 1;
								} break;
					}				

				} break;			
	}
}





