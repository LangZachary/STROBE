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
	static unsigned char	adc_dual_enable = 0;
	static unsigned char	adc_single_enable = 0;
	static unsigned char	current_pot = 1;
	static unsigned char	pot1 = 0;
	static unsigned char	pot2 = 0;
	static unsigned int		math;
	static unsigned char 	color = 0;
	static unsigned char	i;
	static unsigned char	pot1_old = 0;
	static unsigned char	pot2_old = 0;
	

	// Variable passed into the function decides which process is completed.
	// 1 - Single Dial Initialization.
	// 2 - Dual Dial Initialization.
	// 3 - Single Dial General Operation.
	// 4 - Dual Dial General Operation.
	// 5 - Single Dial Deinitialization.
	// 6 - Dual Dial Deinitialization.
	switch (adc_process) {

		// Single Dial Initialization Process //
		case adc_single_init: {

								adc_init();					// Re-initialize the adc.
								Nop();
								pot_level = 0x00;			// Clear the value in the adc register.
								Nop();
								adc_on = 1;					// Turn on the adc module.
								Nop();	
								adc_select = adc_pot2;		// Use the right dial.
					
								current_pot = 2;			// Clear all the variable registers used by				
								pot2 = 0;					// the adc.
								pot2_old = 0;
										
								adc_ready = 0;				// Set up the timer for setting delay
								adc_timer_flag = 0;			// between adc acquisitions.
								adc_count = adc_delay;
								adc_timer = 1;
								adc_single_enable = 1;		// Turn on adc control in the general adc process.

							} break;

		// Dual Dial Initialization Process //
		case adc_dual_init: {

								adc_init();					// Re-initialize the adc.
								Nop();
								pot_level = 0x00;			// Clear the value in the adc register.
								Nop();
								adc_on = 1;					// Turn on the adc module.
								Nop();	
					
								current_pot = 1;			// Clear all the variable registers used by
								pot1 = 0;					// the adc.
								pot2 = 0;
								pot1_old = 0;
								pot2_old = 0;
										
								adc_ready = 0;				// Set up the timer for setting delay
								adc_timer_flag = 0;			// between adc acquisitions.
								adc_count = adc_delay;
								adc_timer = 1;
								adc_dual_enable = 1;			// Turn on adc control in the general adc process.

						} break;

		// Single Dial General Process //
		case adc_single_run: {

								// Check for adc control enabled.
								if (!adc_single_enable) {
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

								if (math == pot2_old) {

									return;
								}

//								strobe_lights(led_run);				// Check the lights.

								pot2_old = math;

								pot2 = (math * 0.392157);	// Convert the number from 0 - 255 to 0 - 100.

								strobe_lights(led_run);				// Check the lights.

								adc_ready = 0;			// Start delay before read and next conversion.

			
								// Figure out the color being changed and change that color.
								switch (oled.menu) {
									case strobe_short_new3b_red:
									case strobe_long_new3b_red:
									case manual_menu2b_red:		{	
																	color = 1;	// Variable for deciding which line to send a progress bar to.

																	// Change the Red brightness targets to the one on the pot.
																	if (!zone_select) {

																		for (i = 1; i <= 12; i++) {
																			zone_brightness_target[i].r = pot2;
																		}

																	} else {

																		zone_brightness_target[zone_select].r = pot2;
																	}

																} break;
									case strobe_short_new3c_green:
									case strobe_long_new3c_green:
									case manual_menu2c_green:	{	
																	color = 2;	// Variable for deciding which line to send a progress bar to.

																	// Change the Green brightness targets to the one on the pot.
																	if (!zone_select) {

																		for (i = 1; i <= 12; i++) {
																			zone_brightness_target[i].g = pot2;
																		}

																	} else {

																		zone_brightness_target[zone_select].g = pot2;
																	}

																} break;
									case strobe_short_new3d_blue:
									case strobe_long_new3d_blue:
									case manual_menu2d_blue:	{	
																	color = 3;	// Variable for deciding which line to send a progress bar to.

																	// Change the Blue brightness targets to the one on the pot.
																	if (!zone_select) {

																		for (i = 1; i <= 12; i++) {
																			zone_brightness_target[i].b = pot2;
																		}

																	} else {

																		zone_brightness_target[zone_select].b = pot2;
																	}

																} break;
									default:					break;
								}
														
								print_progress_bar(color, 9, pot2);																
//								strobe_lights(led_run);				// Check the lights.


							} break;	

		// Dual Dial General Process //
		case adc_dual_run: {

								// Check for adc control enabled.
								if (!adc_dual_enable) {
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
			
												math = pot_level;					// Read the value from the adc.

												strobe_lights(led_run);				// Check the lights.

												if (math != pot1_old) {
													pot1_old = math;
													pot1 = (math * 0.392157);		// Convert number from 0-255 to 0 - 100
													switch (oled.menu) {
														case motion_menu2a:	print_delay(pot1, timeout_delay);	// Print the percent to the display.
																			break;
														case strobe_short_new4:
														case strobe_long_new4:
																			print_delay(pot1, hold_time);		// Print the percent to the display.
																			break;
														case strobe_strobe1a:
																			print_progress_bar(2, 9, pot1);
																			strobelight_time_on = (int)pot1 * 15;
																			strobelight_time_on++;
																			break;
													}
												}

												adc_select = adc_pot2;	// Point the adc to pot 2 for conversion.

												strobe_lights(led_run);	// Check the lights.

												current_pot = 2;
												adc_start = 1;			// Start the conversion.
												adc_ready = 0;			// Start delay before read and next conversion.
											
											} break;
							
									// Pot 2 - current_pot = 2.
									case 2: {
				
												math = pot_level;		// Read the value from the adc.

												strobe_lights(led_run);				// Check the lights.

												if (math != pot2_old) {
													pot2_old = math;
													pot2 = (math * 0.392157);	// Convert number from 0-255 to 0 - 100
													
													switch (oled.menu) {
														case motion_menu2a:	print_ms_lightspread(pot2);
																			break;
														case strobe_short_new4:
														case strobe_long_new4:
																			print_strobe_fadetime(pot2);
																			break;
														case strobe_strobe1a:
																			print_progress_bar(3, 9, pot2);
																			strobelight_time_off = (int)pot2 * 15;
																			strobelight_time_off++;
																			break;																			
													}
												}

												adc_select = adc_pot1;  // Point the adc to pot 1 for conversion.

												strobe_lights(led_run);	// Check the lights.

												current_pot = 1;
												adc_start = 1;			// Start the conversion.
												adc_ready = 0;			// Start delay before read and next conversion.

											} break;
			
									// Error
									default: {
												current_pot = 1;
											} break;
								}				

						} break;	

		// Single Dial Deinitialization Process //
		case adc_single_deinit: {
	
								adc_on = 0;					// Turn off the adc module.
								Nop();
							
								adc_timer = 0;				// Turn off the adc delay timer.
								adc_single_enable = 0;		// Turn off adc control in the general adc process.	

							} break;

		// Dual Dial Deinitialization Process //
		case adc_dual_deinit: {
	
								adc_on = 0;					// Turn off the adc module.
								Nop();
							
								adc_timer = 0;				// Turn off the adc delay timer.
								adc_dual_enable = 0;		// Turn off adc control in the general adc process.	

							} break;

	}
}





