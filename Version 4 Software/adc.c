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
	static unsigned char	ms_adc_enable = 0;
	static unsigned char	manual_adc_enable = 0;
	static unsigned char	current_pot = 1;
	static unsigned char	pot1 = 0;
	static unsigned char	pot2 = 0;
	unsigned int			math = 0;
	unsigned char 			color = 0;
	unsigned char			i;
	

	// Variable passed into the function decides which process is completed.
	// 1 - MS Initialization.
	// 2 - Manual Initialization.
	// 3 - MS General Operation.
	// 4 - Manual General Operation.
	// 5 - MS Deinitialization.
	// 6 - Manual Deinitialization.
	switch (adc_process) {

		// MS Initialization Process //
		case adc_ms_init: {

								adc_init();					// Re-initialize the adc.
								Nop();
								pot_level = 0x00;			// Clear the value in the adc register.
								Nop();
								adc_on = 1;					// Turn on the adc module.
								Nop();	
					
								current_pot = 1;			// Clear all the variable registers used by
								pot1 = 0;					// the adc.
								pot2 = 0;
										
								adc_ready = 0;				// Set up the timer for setting delay
								adc_timer_flag = 0;			// between adc acquisitions.
								adc_count = adc_delay;
								adc_timer = 1;
								ms_adc_enable = 1;			// Turn on adc control in the general adc process.

						} break;

		// Manual Initialization Process //
		case adc_manual_init: {

								adc_init();					// Re-initialize the adc.
								Nop();
								pot_level = 0x00;			// Clear the value in the adc register.
								Nop();
								adc_on = 1;					// Turn on the adc module.
								Nop();	
								adc_select = adc_pot2;		// Use the right dial.
					
								current_pot = 2;			// Clear all the variable registers used by				
								pot2 = 0;					// the adc.
										
								adc_ready = 0;				// Set up the timer for setting delay
								adc_timer_flag = 0;			// between adc acquisitions.
								adc_count = adc_delay;
								adc_timer = 1;
								manual_adc_enable = 1;		// Turn on adc control in the general adc process.

							} break;

		// MS General Process //
		case adc_ms_run: {

								// Check for adc control enabled.
								if (!ms_adc_enable) {
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
			
												math = pot_level;		// Read the value from the adc.
												pot1 = (math / 2.55);	// Convert number from 0-255 to 0 - 100
												Nop();
												adc_select = adc_pot2;	// Point the adc to pot 2 for conversion.
												Nop();
												current_pot = 2;
												Nop();
												adc_start = 1;			// Start the conversion.
												Nop();
												adc_ready = 0;			// Start delay before read and next conversion.
												print_ms_timeout_delay(1, 5, pot1);
												
											} break;
							
									// Pot 2 - current_pot = 2.
									case 2: {
				
												math = pot_level;		// Read the value from the adc.
												pot2 = (math / 2.55);	// Convert number from 0-255 to 0 - 100
												Nop();
												adc_select = adc_pot1;  // Point the adc to pot 1 for conversion.
												Nop();
												current_pot = 1;
												Nop();
												adc_start = 1;			// Start the conversion.
												Nop();
												adc_ready = 0;			// Start delay before read and next conversion.
												print_ms_lightspread(3, 5, pot2);

											} break;
			
									// Error
									default: {
												current_pot = 1;
											} break;
								}				

						} break;	

		// Manual General Process //
		case adc_manual_run: {

								// Check for adc control enabled.
								if (!manual_adc_enable) {
									break;
								}
			
								// Check for the adc delay.
								if (!adc_ready) {
									break;
								}
			
								math = pot_level;		// Read the value from the adc.
								Nop();
								adc_start = 1;			// Start the conversion.
								Nop();
								pot2 = (math / 2.55);	// Convert the number from 0 - 255 to 0 - 100.
								adc_ready = 0;			// Start delay before read and next conversion.
			
								// Figure out the color being changed and change that color.
								switch (oled.menu) {
									case manual_menu1b_red:		{	
																	color = 1;	// Variable for deciding which line to send a progress bar to.

																	// Change the Red brightness targets to the one on the pot.
																	if (!manual_zone_select) {
																		for (i = 1; i <= 12; i++) {
																			zone_brightness_target[i].r = pot2;
																		}
																	} else {
																		zone_brightness_target[manual_zone_select].r = pot2;
																	}

																} break;
									case manual_menu1c_green:	{	
																	color = 2;	// Variable for deciding which line to send a progress bar to.

																	// Change the Green brightness targets to the one on the pot.
																	if (!manual_zone_select) {
																		for (i = 1; i <= 12; i++) {
																			zone_brightness_target[i].g = pot2;
																		}
																	} else {
																		zone_brightness_target[manual_zone_select].g = pot2;
																	}

																} break;
									case manual_menu1d_blue:	{	
																	color = 3;	// Variable for deciding which line to send a progress bar to.

																	// Change the Blue brightness targets to the one on the pot.
																	if (!manual_zone_select) {
																		for (i = 1; i <= 12; i++) {
																			zone_brightness_target[i].b = pot2;
																		}
																	} else {
																		zone_brightness_target[manual_zone_select].b = pot2;
																	}

																} break;
									default:					break;
								}
														
								print_progress_bar(color, 9, pot2);																

							} break;	

		// MS Deinitialization Process //
		case adc_ms_deinit: {
	
								adc_on = 0;					// Turn off the adc module.
								Nop();
							
								adc_timer = 0;				// Turn off the adc delay timer.
								ms_adc_enable = 0;			// Turn off adc control in the general adc process.	

							} break;

		// Manual Deinitialization Process //
		case adc_manual_deinit: {
	
								adc_on = 0;					// Turn off the adc module.
								Nop();
							
								adc_timer = 0;				// Turn off the adc delay timer.
								manual_adc_enable = 0;		// Turn off adc control in the general adc process.	

							} break;

	
	}
}





