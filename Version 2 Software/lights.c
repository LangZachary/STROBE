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
void strobe_lights(void)
{

	if (frequency_trigger) {
		lights_frequency();
		frequency_trigger = 0;
	}

	if (dutycycle_trigger) {
		lights_dutycycle();
		dutycycle_trigger = 0;
	}

}


void lights_frequency(void)
{
	static unsigned char current_zone = 1;

	// Cycle through all twelve zones.
	if (current_zone == 12) {
		current_zone = 1;
		
		// Every set amount of cycles fade to the zone's target brightness.
		if (fade_speed == 0) {
			fade_speed = fade_fast;
		} else {
			fade_speed--;
		}
	} else {
		current_zone++;
	}



	// Turn off the lights in the current zone and then reload the
	// brightness variable with the value in the buffer.
	switch (current_zone) {
		
		// ZONE 1 //
		case 1:		z1r = 0;
					z1g = 0;
					z1b = 0;
					zone_brightness[1] = zone_brightness_buffer[1];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
					if (fade_speed == 0) {

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
					}
					break;
		
		// ZONE 2 //
		case 2:		z2r = 0;
					z2g = 0;
					z2b = 0;
					zone_brightness[2] = zone_brightness_buffer[2];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
					if (fade_speed == 0) {

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
					}
					break;
		
		// ZONE 3 //
		case 3:		z3r = 0;
					z3g = 0;
					z3b = 0;
					zone_brightness[3] = zone_brightness_buffer[3];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
					if (fade_speed == 0) {

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
					}
					break;
		
		// ZONE 4 //
		case 4:		z4r = 0;
					z4g = 0;
					z4b = 0;
					zone_brightness[4] = zone_brightness_buffer[4];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
					if (fade_speed == 0) {

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
					}
					break;
		
		// ZONE 5 //
		case 5:		z5r = 0;
					z5g = 0;
					z5b = 0;
					zone_brightness[5] = zone_brightness_buffer[5];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
					if (fade_speed == 0) {

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
					}
					break;
		
		// ZONE 6 //
		case 6:		z6r = 0;
					z6g = 0;
					z6b = 0;
					zone_brightness[6] = zone_brightness_buffer[6];

					// Every number of cycles controlled by fade_speed, change the brightness of the
					// zone's leds towards the target.
					if (fade_speed == 0) {

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
					}
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
}



		