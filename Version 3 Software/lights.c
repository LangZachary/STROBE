/*****************************************************************************************
 *                                      LIGHTS											 *
 *****************************************************************************************/

/*  Root function for processing lights.
 *  The function checks if the frequency trigger is enabled first.
 *		On frequency trigger a function is ran that turns all the lights off at a set
 *		frequency.  The frequency is set to 100Hz.
 *	The function then checks if dutcycle trigger is enabled.
 *		On duty cycle trigger a function is ran that controls each individual zone and
 *		color of light's brightness.  This is governed by the zone_brightness_buffer.
 */
void strobe_lights(unsigned char lights_process)
{

	static unsigned char	lights_enable = 0;

	// Variable passed into the function decides which process is completed.
	// 1 - Initialization process for motion sensing mode.
	// 2 - Deinitialization process.
	// 3 - General operation.
	// 4 - Initialization process for other modes.
	switch (lights_process) {

		// Motion Sensing Mode Initialization.
		case 1: {
					
					frequency_timer = 1;		// Enable the timers for the lights.
					dutycycle_timer = 1;

					lights_enable = 1;			// Enable light action.
			} break;

		// Other Mode Initialization.
		case 2: {


			} break;

		// General Operation.
		case 3: {
					
					// Check if lights in an enabled mode.
					if (!lights_enable) {
						return;
					}
//					if (frequency_trigger) {
//						lights_frequency();
//						frequency_trigger = 0;
//					}
				
//					if (dutycycle_trigger) {
//					lights_dutycycle();
//						dutycycle_trigger = 0;
//					}
			} break;				
	}


}


void lights_frequency(void)
{
	static unsigned char current_zone = 1;

	// Cycle through all twelve zones.
	if (current_zone == 12) {
		current_zone = 1;

	/*	CODE FOR ADJUST FADE SPEED	
		// Every set amount of cycles fade to the zone's target brightness.
		if (fade_speed == 0) {
			fade_speed = fade_fast;
		} else {
			fade_speed--;
		}
	*/
	} else {
		current_zone++;
	}

	// Turn off the lights in the current zone and then reload the
	// brightness variable with the value in the buffer.
	switch (current_zone) {
		
		// ZONE 1 //
		case 1:		z1r = 0;
					Nop();
					z1g = 0;
					Nop();
					z1b = 0;
					Nop();
					zone_brightness[1] = zone_brightness_buffer[1];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[1].r > zone_brightness_buffer[1].r) {
							zone_brightness_buffer[1].r++;
						} else if (zone_brightness_target[1].r < zone_brightness_buffer[1].r) {
							zone_brightness_buffer[1].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[1].g > zone_brightness_buffer[1].g) {
							zone_brightness_buffer[1].g++;
						} else if (zone_brightness_target[1].g < zone_brightness_buffer[1].g) {
							zone_brightness_buffer[1].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[1].b > zone_brightness_buffer[1].b) {
							zone_brightness_buffer[1].b++;
						} else if (zone_brightness_target[1].b < zone_brightness_buffer[1].b) {
							zone_brightness_buffer[1].b--;
						}
//					}
					break;
		
		// ZONE 2 //
		case 2:		z2r = 0;
					Nop();
					z2g = 0;
					Nop();
					z2b = 0;
					Nop();
					zone_brightness[2] = zone_brightness_buffer[2];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[2].r > zone_brightness_buffer[2].r) {
							zone_brightness_buffer[2].r++;
						} else if (zone_brightness_target[2].r < zone_brightness_buffer[2].r) {
							zone_brightness_buffer[2].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[2].g > zone_brightness_buffer[2].g) {
							zone_brightness_buffer[2].g++;
						} else if (zone_brightness_target[2].g < zone_brightness_buffer[2].g) {
							zone_brightness_buffer[2].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[2].b > zone_brightness_buffer[2].b) {
							zone_brightness_buffer[2].b++;
						} else if (zone_brightness_target[2].b < zone_brightness_buffer[2].b) {
							zone_brightness_buffer[2].b--;
						}
//					}
					break;
		
		// ZONE 3 //
		case 3:		z3r = 0;
					Nop();
					z3g = 0;
					Nop();
					z3b = 0;
					Nop();
					zone_brightness[3] = zone_brightness_buffer[3];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[3].r > zone_brightness_buffer[3].r) {
							zone_brightness_buffer[3].r++;
						} else if (zone_brightness_target[3].r < zone_brightness_buffer[3].r) {
							zone_brightness_buffer[3].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[3].g > zone_brightness_buffer[3].g) {
							zone_brightness_buffer[3].g++;
						} else if (zone_brightness_target[3].g < zone_brightness_buffer[3].g) {
							zone_brightness_buffer[3].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[3].b > zone_brightness_buffer[3].b) {
							zone_brightness_buffer[3].b++;
						} else if (zone_brightness_target[3].b < zone_brightness_buffer[3].b) {
							zone_brightness_buffer[3].b--;
						}
//					}
					break;
		
		// ZONE 4 //
		case 4:		z4r = 0;
					Nop();
					z4g = 0;
					Nop();
					z4b = 0;
					Nop();
					zone_brightness[4] = zone_brightness_buffer[4];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[4].r > zone_brightness_buffer[4].r) {
							zone_brightness_buffer[4].r++;
						} else if (zone_brightness_target[4].r < zone_brightness_buffer[4].r) {
							zone_brightness_buffer[4].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[4].g > zone_brightness_buffer[4].g) {
							zone_brightness_buffer[4].g++;
						} else if (zone_brightness_target[4].g < zone_brightness_buffer[4].g) {
							zone_brightness_buffer[4].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[4].b > zone_brightness_buffer[4].b) {
							zone_brightness_buffer[4].b++;
						} else if (zone_brightness_target[4].b < zone_brightness_buffer[4].b) {
							zone_brightness_buffer[4].b--;
						}
//					}
					break;
		
		// ZONE 5 //
		case 5:		z5r = 0;
					Nop();
					z5g = 0;
					Nop();
					z5b = 0;
					Nop();
					zone_brightness[5] = zone_brightness_buffer[5];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[5].r > zone_brightness_buffer[5].r) {
							zone_brightness_buffer[5].r++;
						} else if (zone_brightness_target[5].r < zone_brightness_buffer[5].r) {
							zone_brightness_buffer[5].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[5].g > zone_brightness_buffer[5].g) {
							zone_brightness_buffer[5].g++;
						} else if (zone_brightness_target[5].g < zone_brightness_buffer[5].g) {
							zone_brightness_buffer[5].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[5].b > zone_brightness_buffer[5].b) {
							zone_brightness_buffer[5].b++;
						} else if (zone_brightness_target[5].b < zone_brightness_buffer[5].b) {
							zone_brightness_buffer[5].b--;
						}
//					}
					break;
		
		// ZONE 6 //
		case 6:		z6r = 0;
					Nop();
					z6g = 0;
					Nop();
					z6b = 0;
					Nop();
					zone_brightness[6] = zone_brightness_buffer[6];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[6].r > zone_brightness_buffer[6].r) {
							zone_brightness_buffer[6].r++;
						} else if (zone_brightness_target[6].r < zone_brightness_buffer[6].r) {
							zone_brightness_buffer[6].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[6].g > zone_brightness_buffer[6].g) {
							zone_brightness_buffer[6].g++;
						} else if (zone_brightness_target[6].g < zone_brightness_buffer[6].g) {
							zone_brightness_buffer[6].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[6].b > zone_brightness_buffer[6].b) {
							zone_brightness_buffer[6].b++;
						} else if (zone_brightness_target[6].b < zone_brightness_buffer[6].b) {
							zone_brightness_buffer[6].b--;
						}
//					}
					break;

		// ZONE 7 //
		case 7:		z7r = 0;
					Nop();
					z7g = 0;
					Nop();
					z7b = 0;
					Nop();
					zone_brightness[7] = zone_brightness_buffer[7];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[7].r > zone_brightness_buffer[7].r) {
							zone_brightness_buffer[7].r++;
						} else if (zone_brightness_target[7].r < zone_brightness_buffer[7].r) {
							zone_brightness_buffer[7].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[7].g > zone_brightness_buffer[7].g) {
							zone_brightness_buffer[7].g++;
						} else if (zone_brightness_target[7].g < zone_brightness_buffer[7].g) {
							zone_brightness_buffer[7].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[7].b > zone_brightness_buffer[7].b) {
							zone_brightness_buffer[7].b++;
						} else if (zone_brightness_target[7].b < zone_brightness_buffer[7].b) {
							zone_brightness_buffer[7].b--;
						}
//					}
					break;

		// ZONE 8 //
		case 8:		z8r = 0;
					Nop();
					z8g = 0;
					Nop();
					z8b = 0;
					Nop();
					zone_brightness[8] = zone_brightness_buffer[8];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[8].r > zone_brightness_buffer[8].r) {
							zone_brightness_buffer[8].r++;
						} else if (zone_brightness_target[8].r < zone_brightness_buffer[8].r) {
							zone_brightness_buffer[8].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[8].g > zone_brightness_buffer[8].g) {
							zone_brightness_buffer[8].g++;
						} else if (zone_brightness_target[8].g < zone_brightness_buffer[8].g) {
							zone_brightness_buffer[8].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[8].b > zone_brightness_buffer[8].b) {
							zone_brightness_buffer[8].b++;
						} else if (zone_brightness_target[8].b < zone_brightness_buffer[8].b) {
							zone_brightness_buffer[8].b--;
						}
//					}
					break;

		// ZONE 9 //
		case 9:		z9r = 0;
					Nop();
					z9g = 0;
					Nop();
					z9b = 0;
					Nop();
					zone_brightness[9] = zone_brightness_buffer[9];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[9].r > zone_brightness_buffer[9].r) {
							zone_brightness_buffer[9].r++;
						} else if (zone_brightness_target[9].r < zone_brightness_buffer[9].r) {
							zone_brightness_buffer[9].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[9].g > zone_brightness_buffer[9].g) {
							zone_brightness_buffer[9].g++;
						} else if (zone_brightness_target[9].g < zone_brightness_buffer[9].g) {
							zone_brightness_buffer[9].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[9].b > zone_brightness_buffer[9].b) {
							zone_brightness_buffer[9].b++;
						} else if (zone_brightness_target[9].b < zone_brightness_buffer[9].b) {
							zone_brightness_buffer[9].b--;
						}
//					}
					break;

		// ZONE 10 //
		case 10:	z10r = 0;
					Nop();
					z10g = 0;
					Nop();
					z10b = 0;
					Nop();
					zone_brightness[10] = zone_brightness_buffer[10];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[10].r > zone_brightness_buffer[10].r) {
							zone_brightness_buffer[10].r++;
						} else if (zone_brightness_target[10].r < zone_brightness_buffer[10].r) {
							zone_brightness_buffer[10].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[10].g > zone_brightness_buffer[10].g) {
							zone_brightness_buffer[10].g++;
						} else if (zone_brightness_target[10].g < zone_brightness_buffer[10].g) {
							zone_brightness_buffer[10].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[10].b > zone_brightness_buffer[10].b) {
							zone_brightness_buffer[10].b++;
						} else if (zone_brightness_target[10].b < zone_brightness_buffer[10].b) {
							zone_brightness_buffer[10].b--;
						}
//					}
					break;

		// ZONE 11 //
		case 11:	z11r = 0;
					Nop();
					z11g = 0;
					Nop();
					z11b = 0;
					Nop();
					zone_brightness[11] = zone_brightness_buffer[11];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[11].r > zone_brightness_buffer[11].r) {
							zone_brightness_buffer[11].r++;
						} else if (zone_brightness_target[11].r < zone_brightness_buffer[11].r) {
							zone_brightness_buffer[11].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[11].g > zone_brightness_buffer[11].g) {
							zone_brightness_buffer[11].g++;
						} else if (zone_brightness_target[11].g < zone_brightness_buffer[11].g) {
							zone_brightness_buffer[11].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[11].b > zone_brightness_buffer[11].b) {
							zone_brightness_buffer[11].b++;
						} else if (zone_brightness_target[11].b < zone_brightness_buffer[11].b) {
							zone_brightness_buffer[11].b--;
						}
//					}
					break;

		// ZONE 12 //
		case 12:	z12r = 0;
					Nop();
					z12g = 0;
					Nop();
					z12b = 0;
					Nop();
					zone_brightness[12] = zone_brightness_buffer[12];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
//					if (fade_speed == 0) {

						// RED LED brightness change towards the target.
						if (zone_brightness_target[12].r > zone_brightness_buffer[12].r) {
							zone_brightness_buffer[12].r++;
						} else if (zone_brightness_target[12].r < zone_brightness_buffer[12].r) {
							zone_brightness_buffer[12].r--;
						}

						// GREEN LED brightness change towards the target.
						if (zone_brightness_target[12].g > zone_brightness_buffer[12].g) {
							zone_brightness_buffer[12].g++;
						} else if (zone_brightness_target[12].g < zone_brightness_buffer[12].g) {
							zone_brightness_buffer[12].g--;
						}

						// BLUE LED brightness change towards the target.
						if (zone_brightness_target[12].b > zone_brightness_buffer[12].b) {
							zone_brightness_buffer[12].b++;
						} else if (zone_brightness_target[12].b < zone_brightness_buffer[12].b) {
							zone_brightness_buffer[12].b--;
						}
//					}
					break;

		default:	// Error Management.
					current_zone = 1;
					break;
	}
}

void lights_dutycycle(void)
{

	// ZONE 1 //

	// Red //
	if (!z1r) {
		if (zone_brightness[1].r == 100) {
			z1r = 1;
		} else {
			zone_brightness[1].r++;
		}
	}

	// Green //
	if (!z1g) {
		if (zone_brightness[1].g == 100) {
			z1g = 1;
		} else {
			zone_brightness[1].g++;
		}
	}

	// Blue //
	if (!z1b) {
		if (zone_brightness[1].b == 100) {
			z1b = 1;
		} else {
			zone_brightness[1].b++;
		}
	}

	// ZONE 2 //

	// Red //
	if (!z2r) {
		if (zone_brightness[2].r == 100) {
			z2r = 1;
		} else {
			zone_brightness[2].r++;
		}
	}

	// Green //
	if (!z2g) {
		if (zone_brightness[2].g == 100) {
			z2g = 1;
		} else {
			zone_brightness[2].g++;
		}
	}

	// Blue //
	if (!z2b) {
		if (zone_brightness[2].b == 100) {
			z2b = 1;
		} else {
			zone_brightness[2].b++;
		}
	}

	// ZONE 3 //

	// Red //
	if (!z3r) {
		if (zone_brightness[3].r == 100) {
			z3r = 1;
		} else {
			zone_brightness[3].r++;
		}
	}

	// Green //
	if (!z3g) {
		if (zone_brightness[3].g == 100) {
			z3g = 1;
		} else {
			zone_brightness[3].g++;
		}
	}

	// Blue //
	if (!z3b) {
		if (zone_brightness[3].b == 100) {
			z3b = 1;
		} else {
			zone_brightness[3].b++;
		}
	}

	// ZONE 4 //

	// Red //
	if (!z4r) {
		if (zone_brightness[4].r == 100) {
			z4r = 1;
		} else {
			zone_brightness[4].r++;
		}
	}

	// Green //
	if (!z4g) {
		if (zone_brightness[4].g == 100) {
			z4g = 1;
		} else {
			zone_brightness[4].g++;
		}
	}

	// Blue //
	if (!z4b) {
		if (zone_brightness[4].b == 100) {
			z4b = 1;
		} else {
			zone_brightness[4].b++;
		}
	}

	// ZONE 5 //

	// Red //
	if (!z5r) {
		if (zone_brightness[5].r == 100) {
			z5r = 1;
		} else {
			zone_brightness[5].r++;
		}
	}

	// Green //
	if (!z5g) {
		if (zone_brightness[5].g == 100) {
			z5g = 1;
		} else {
			zone_brightness[5].g++;
		}
	}

	// Blue //
	if (!z5b) {
		if (zone_brightness[5].b == 100) {
			z5b = 1;
		} else {
			zone_brightness[5].b++;
		}
	}

	// ZONE 6 //

	// Red //
	if (!z6r) {
		if (zone_brightness[6].r == 100) {
			z6r = 1;
		} else {
			zone_brightness[6].r++;
		}
	}

	// Green //
	if (!z6g) {
		if (zone_brightness[6].g == 100) {
			z6g = 1;
		} else {
			zone_brightness[6].g++;
		}
	}

	// Blue //
	if (!z6b) {
		if (zone_brightness[6].b == 100) {
			z6b = 1;
		} else {
			zone_brightness[6].b++;
		}
	}

	// ZONE 7 //

	// Red //
	if (!z7r) {
		if (zone_brightness[7].r == 100) {
			z7r = 1;
		} else {
			zone_brightness[7].r++;
		}
	}

	// Green //
	if (!z7g) {
		if (zone_brightness[7].g == 100) {
			z7g = 1;
		} else {
			zone_brightness[7].g++;
		}
	}

	// Blue //
	if (!z7b) {
		if (zone_brightness[7].b == 100) {
			z7b = 1;
		} else {
			zone_brightness[7].b++;
		}
	}

	// ZONE 8 //

	// Red //
	if (!z8r) {
		if (zone_brightness[8].r == 100) {
			z8r = 1;
		} else {
			zone_brightness[8].r++;
		}
	}

	// Green //
	if (!z8g) {
		if (zone_brightness[8].g == 100) {
			z8g = 1;
		} else {
			zone_brightness[8].g++;
		}
	}

	// Blue //
	if (!z8b) {
		if (zone_brightness[8].b == 100) {
			z8b = 1;
		} else {
			zone_brightness[8].b++;
		}
	}

	// ZONE 9 //

	// Red //
	if (!z9r) {
		if (zone_brightness[9].r == 100) {
			z9r = 1;
		} else {
			zone_brightness[9].r++;
		}
	}

	// Green //
	if (!z9g) {
		if (zone_brightness[9].g == 100) {
			z9g = 1;
		} else {
			zone_brightness[9].g++;
		}
	}

	// Blue //
	if (!z9b) {
		if (zone_brightness[9].b == 100) {
			z9b = 1;
		} else {
			zone_brightness[9].b++;
		}
	}

	// ZONE 10 //

	// Red //
	if (!z10r) {
		if (zone_brightness[10].r == 100) {
			z10r = 1;
		} else {
			zone_brightness[10].r++;
		}
	}

	// Green //
	if (!z10g) {
		if (zone_brightness[10].g == 100) {
			z10g = 1;
		} else {
			zone_brightness[10].g++;
		}
	}

	// Blue //
	if (!z10b) {
		if (zone_brightness[10].b == 100) {
			z10b = 1;
		} else {
			zone_brightness[10].b++;
		}
	}

	// ZONE 11 //

	// Red //
	if (!z11r) {
		if (zone_brightness[11].r == 100) {
			z11r = 1;
		} else {
			zone_brightness[11].r++;
		}
	}

	// Green //
	if (!z11g) {
		if (zone_brightness[11].g == 100) {
			z11g = 1;
		} else {
			zone_brightness[11].g++;
		}
	}

	// Blue //
	if (!z11b) {
		if (zone_brightness[11].b == 100) {
			z11b = 1;
		} else {
			zone_brightness[11].b++;
		}
	}

	// ZONE 12 //

	// Red //
	if (!z12r) {
		if (zone_brightness[12].r == 100) {
			z12r = 1;
		} else {
			zone_brightness[12].r++;
		}
	}

	// Green //
	if (!z12g) {
		if (zone_brightness[12].g == 100) {
			z12g = 1;
		} else {
			zone_brightness[12].g++;
		}
	}

	// Blue //
	if (!z12b) {
		if (zone_brightness[12].b == 100) {
			z12b = 1;
		} else {
			zone_brightness[12].b++;
		}
	}
}



		