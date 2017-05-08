/*****************************************************************************************
 *                                 MOTION SENSORS										 *
 *****************************************************************************************/

/*  Root function for motion sensors.
 */
void strobe_motionsensors(unsigned char ms_process)
{
	unsigned char i;

	// Bit array for telling if a zone detects someone in it.
	// 1 - Zone detects a target.
	// 0 - Zone does not detect a target.
	static unsigned char 	zone_active[13] = {0};

	// Array for keeping track when to turn off a zone after no new activity has been detected in
	// it.  This value is counted down each time the motion sensors are rechecked (100ms).
	// 10 >> 1s
	// 200 >> 20s.
	static unsigned int		zone_timeout[13] = {0};

	// Variable for the current state of the motion sensors.
	static unsigned char 	zone_check[13] = {0};

	// Variable for the previous state of the motion sensors.
	static unsigned char 	zone_check_old[13] = {0};

	static unsigned char	ms_enable = 0;
	static unsigned char	new_activity = 0;
	static unsigned char	new_timeout = 0;

	// Variable passed into the function decides which process is completed.
	// 1 - Initialization process for motion sensing mode.
	// 2 - Deinitialization process.
	// 3 - Motion sensor checking.
	// 4 - Motion sensor action.
	switch (ms_process) {

		// Motion Sensor Initialization. (32 us)
		case ms_init: {

					// Clear the registers that keep track of motion sensor states.
					for (i = 1; i <= 12; i++) {

						zone_check[i] = 0;
						zone_check_old[i] = 0;
						zone_timeout[i] = 0;
						zone_active[i] = 0;
					}
					
					new_timeout = 0;
					new_activity = 0;

					ms_ready = 0;			// Set up timer for setting delay between ms
					ms_timer_flag = 0;		// checks.
					ms_count = ms_delay;					
					ms_timer = 1;			// Enable the timers for the motion sensors.
					ms_enable = 1;			// Enable motion sensor action.

			} break;

		// Motion Sensor Checking //
		case ms_check: {

					// Check if motion sensor action is enabled. Enabled in the ms initialize
					// routine and disabled in the deinitialize routine.
					if (!ms_enable) {
						break;
					}

					// Only check and act upon the motion sensors when ms_ready is set. This register is
					// controlled by Timer7 and by default resets every 100ms.
					if (!ms_ready) {
						break;
					}

					// Motion Sensor Check and Action.
					// Read the motion sensors.
					zone_check[1] = ms1;
					Nop();
					zone_check[2] = ms2;
					Nop();
					zone_check[3] = ms3;
					Nop();
					zone_check[4] = ms4;
					Nop();
					zone_check[5] = ms5;
					Nop();
					zone_check[6] = ms6;
					Nop();
					zone_check[7] = ms7;
					Nop();
					zone_check[8] = ms8;
					Nop();
					zone_check[9] = ms9;
					Nop();
					zone_check[10] = ms10;
					Nop();
					zone_check[11] = ms11;
					Nop();
					zone_check[12] = ms12;
					Nop();

					// Cross check the new motion sensors state with the previous one. If new activity
					// is detected, ignore activity in adjacent zones and assume they have moved.
					for (i = 1; i <= 12; i++) {

						if (zone_check[i] != zone_check_old[i]) {

							// New activity is detected, react accordingly.
							if (zone_check[i]) {

								switch (i) {

									case 1: {
												zone_active[1] = 1;			// Change the current zone to active.
												zone_active[12] = 0;		// Turn off adjacent zones.
												zone_active[2] = 0;
										} break;	

									case 12: {
												zone_active[12] = 1;		// Change the current zone to active.
												zone_active[11] = 0;		// Turn off adjacent zones.
												zone_active[1] = 0;
										} break;

									default: {
												zone_active[i] = 1;			// Change the current zone to active.
												zone_active[i - 1] = 0;		// Turn off adjacent zones.
												zone_active[i + 1] = 0;	
										} break;
								}	

							new_activity = 1;		// Trigger a needed light change.							
							
							// New inactivity.
							} else {
								
								// If that zone was active before, start time out delay.
								if (zone_active[i]) {
									zone_timeout[i] = zone_timeout_delay;
									new_timeout = 1;
								}
							}

							zone_check_old[i] = zone_check[i];		// Save the change.
						}
					}

					// See if there are timeouts to countdown.
					if (!new_timeout) {
						break;
					}

					new_timeout = 0;						// Clear the new_timeout, if there is a current
															// timeout delay this will be set again.
			
					// Cycle through each zone's timeout.
					for (i = 1; i <= 12; i++) {
			
						switch (zone_timeout[i]) {

							// No timeout delay.
							case 0: break;

							// Timeout delay is over. Deactivate that zone.
							case 1: {
										zone_timeout[i]--;
										zone_active[i] = 0;
										new_activity = 1;
								} break;

							// Timeout delay is still counting. Set new_timeout so this loop will
							// keep counting.
							default: {
										zone_timeout[i]--;
										new_timeout = 1;
								} break;
						}
					}

					// Start delay before another check of the motion sensors.
					ms_ready = 0;		
										
			} break;

		// Motion Sensor Action //
		case ms_action: {

					// Check if motion sensor action is enabled. Enabled in the ms initialize
					// routine and disabled in the deinitialize routine.
					if (!ms_enable) {
						break;
					}

					// Adjust Zone 1 Lights.
					if (zone_active[1]) {
						zone_brightness_target[1].r = 100;
						zone_brightness_target[1].g = 100;
						zone_brightness_target[1].b = 100;
					} else if (zone_active[12] || zone_active[2]) {
						zone_brightness_target[1].r = adjacent_brightness;
						zone_brightness_target[1].g = adjacent_brightness;
						zone_brightness_target[1].b = adjacent_brightness;
					} else if (zone_active[11] || zone_active[3]) {
						zone_brightness_target[1].r = adjacent2_brightness;
						zone_brightness_target[1].g = adjacent2_brightness;
						zone_brightness_target[1].b = adjacent2_brightness;
					} else if (zone_active[10] || zone_active[4]) {
						zone_brightness_target[1].r = adjacent3_brightness;
						zone_brightness_target[1].g = adjacent3_brightness;
						zone_brightness_target[1].b = adjacent3_brightness;
					} else {
						zone_brightness_target[1].r = 0;
						zone_brightness_target[1].g = 0;
						zone_brightness_target[1].b = 0;
					}
				
					// Adjust Zone 2 Lights.
					if (zone_active[2]) {
						zone_brightness_target[2].r = 100;
						zone_brightness_target[2].g = 100;
						zone_brightness_target[2].b = 100;
					} else if (zone_active[1] || zone_active[3]) {
						zone_brightness_target[2].r = adjacent_brightness;
						zone_brightness_target[2].g = adjacent_brightness;
						zone_brightness_target[2].b = adjacent_brightness;
					} else if (zone_active[12] || zone_active[4]) {
						zone_brightness_target[2].r = adjacent2_brightness;
						zone_brightness_target[2].g = adjacent2_brightness;
						zone_brightness_target[2].b = adjacent2_brightness;
					} else if (zone_active[11] || zone_active[5]) {
						zone_brightness_target[2].r = adjacent3_brightness;
						zone_brightness_target[2].g = adjacent3_brightness;
						zone_brightness_target[2].b = adjacent3_brightness;
					} else {
						zone_brightness_target[2].r = 0;
						zone_brightness_target[2].g = 0;
						zone_brightness_target[2].b = 0;
					}
				
					// Adjust Zone 3 Lights.
					if (zone_active[3]) {
						zone_brightness_target[3].r = 100;
						zone_brightness_target[3].g = 100;
						zone_brightness_target[3].b = 100;
					} else if (zone_active[2] || zone_active[4]) {
						zone_brightness_target[3].r = adjacent_brightness;
						zone_brightness_target[3].g = adjacent_brightness;
						zone_brightness_target[3].b = adjacent_brightness;
					} else if (zone_active[1] || zone_active[5]) {
						zone_brightness_target[3].r = adjacent2_brightness;
						zone_brightness_target[3].g = adjacent2_brightness;
						zone_brightness_target[3].b = adjacent2_brightness;
					} else if (zone_active[12] || zone_active[6]) {
						zone_brightness_target[3].r = adjacent3_brightness;
						zone_brightness_target[3].g = adjacent3_brightness;
						zone_brightness_target[3].b = adjacent3_brightness;
					} else {
						zone_brightness_target[3].r = 0;
						zone_brightness_target[3].g = 0;
						zone_brightness_target[3].b = 0;
					}
				
					// Adjust Zone 4 Lights.
					if (zone_active[4]) {
						zone_brightness_target[4].r = 100;
						zone_brightness_target[4].g = 100;
						zone_brightness_target[4].b = 100;
					} else if (zone_active[3] || zone_active[5]) {
						zone_brightness_target[4].r = adjacent_brightness;
						zone_brightness_target[4].g = adjacent_brightness;
						zone_brightness_target[4].b = adjacent_brightness;
					} else if (zone_active[2] || zone_active[6]) {
						zone_brightness_target[4].r = adjacent2_brightness;
						zone_brightness_target[4].g = adjacent2_brightness;
						zone_brightness_target[4].b = adjacent2_brightness;
					} else if (zone_active[1] || zone_active[7]) {
						zone_brightness_target[4].r = adjacent3_brightness;
						zone_brightness_target[4].g = adjacent3_brightness;
						zone_brightness_target[4].b = adjacent3_brightness;
					} else {
						zone_brightness_target[4].r = 0;
						zone_brightness_target[4].g = 0;
						zone_brightness_target[4].b = 0;
					}
				
					// Adjust Zone 5 Lights.
					if (zone_active[5]) {
						zone_brightness_target[5].r = 100;
						zone_brightness_target[5].g = 100;
						zone_brightness_target[5].b = 100;
					} else if (zone_active[4] || zone_active[6]) {
						zone_brightness_target[5].r = adjacent_brightness;
						zone_brightness_target[5].g = adjacent_brightness;
						zone_brightness_target[5].b = adjacent_brightness;
					} else if (zone_active[3] || zone_active[7]) {
						zone_brightness_target[5].r = adjacent2_brightness;
						zone_brightness_target[5].g = adjacent2_brightness;
						zone_brightness_target[5].b = adjacent2_brightness;
					} else if (zone_active[2] || zone_active[8]) {
						zone_brightness_target[5].r = adjacent3_brightness;
						zone_brightness_target[5].g = adjacent3_brightness;
						zone_brightness_target[5].b = adjacent3_brightness;
					} else {
						zone_brightness_target[5].r = 0;
						zone_brightness_target[5].g = 0;
						zone_brightness_target[5].b = 0;
					}
				
					// Adjust Zone 6 Lights.
					if (zone_active[6]) {
						zone_brightness_target[6].r = 100;
						zone_brightness_target[6].g = 100;
						zone_brightness_target[6].b = 100;
					} else if (zone_active[5] || zone_active[7]) {
						zone_brightness_target[6].r = adjacent_brightness;
						zone_brightness_target[6].g = adjacent_brightness;
						zone_brightness_target[6].b = adjacent_brightness;
					} else if (zone_active[4] || zone_active[8]) {
						zone_brightness_target[6].r = adjacent2_brightness;
						zone_brightness_target[6].g = adjacent2_brightness;
						zone_brightness_target[6].b = adjacent2_brightness;
					} else if (zone_active[3] || zone_active[9]) {
						zone_brightness_target[6].r = adjacent3_brightness;
						zone_brightness_target[6].g = adjacent3_brightness;
						zone_brightness_target[6].b = adjacent3_brightness;
					} else {
						zone_brightness_target[6].r = 0;
						zone_brightness_target[6].g = 0;
						zone_brightness_target[6].b = 0;
					}
				
					// Adjust Zone 7 Lights.
					if (zone_active[7]) {
						zone_brightness_target[7].r = 100;
						zone_brightness_target[7].g = 100;
						zone_brightness_target[7].b = 100;
					} else if (zone_active[6] || zone_active[8]) {
						zone_brightness_target[7].r = adjacent_brightness;
						zone_brightness_target[7].g = adjacent_brightness;
						zone_brightness_target[7].b = adjacent_brightness;
					} else if (zone_active[5] || zone_active[9]) {
						zone_brightness_target[7].r = adjacent2_brightness;
						zone_brightness_target[7].g = adjacent2_brightness;
						zone_brightness_target[7].b = adjacent2_brightness;
					} else if (zone_active[4] || zone_active[10]) {
						zone_brightness_target[7].r = adjacent3_brightness;
						zone_brightness_target[7].g = adjacent3_brightness;
						zone_brightness_target[7].b = adjacent3_brightness;
					} else {
						zone_brightness_target[7].r = 0;
						zone_brightness_target[7].g = 0;
						zone_brightness_target[7].b = 0;
					}
				
					// Adjust Zone 8 Lights.
					if (zone_active[8]) {
						zone_brightness_target[8].r = 100;
						zone_brightness_target[8].g = 100;
						zone_brightness_target[8].b = 100;
					} else if (zone_active[7] || zone_active[9]) {
						zone_brightness_target[8].r = adjacent_brightness;
						zone_brightness_target[8].g = adjacent_brightness;
						zone_brightness_target[8].b = adjacent_brightness;
					} else if (zone_active[6] || zone_active[10]) {
						zone_brightness_target[8].r = adjacent2_brightness;
						zone_brightness_target[8].g = adjacent2_brightness;
						zone_brightness_target[8].b = adjacent2_brightness;
					} else if (zone_active[5] || zone_active[11]) {
						zone_brightness_target[8].r = adjacent3_brightness;
						zone_brightness_target[8].g = adjacent3_brightness;
						zone_brightness_target[8].b = adjacent3_brightness;
					} else {
						zone_brightness_target[8].r = 0;
						zone_brightness_target[8].g = 0;
						zone_brightness_target[8].b = 0;
					}
				
					// Adjust Zone 9 Lights.
					if (zone_active[9]) {
						zone_brightness_target[9].r = 100;
						zone_brightness_target[9].g = 100;
						zone_brightness_target[9].b = 100;
					} else if (zone_active[8] || zone_active[10]) {
						zone_brightness_target[9].r = adjacent_brightness;
						zone_brightness_target[9].g = adjacent_brightness;
						zone_brightness_target[9].b = adjacent_brightness;
					} else if (zone_active[7] || zone_active[11]) {
						zone_brightness_target[9].r = adjacent2_brightness;
						zone_brightness_target[9].g = adjacent2_brightness;
						zone_brightness_target[9].b = adjacent2_brightness;
					} else if (zone_active[6] || zone_active[12]) {
						zone_brightness_target[9].r = adjacent3_brightness;
						zone_brightness_target[9].g = adjacent3_brightness;
						zone_brightness_target[9].b = adjacent3_brightness;
					} else {
						zone_brightness_target[9].r = 0;
						zone_brightness_target[9].g = 0;
						zone_brightness_target[9].b = 0;
					}
				
					// Adjust Zone 10 Lights.
					if (zone_active[10]) {
						zone_brightness_target[10].r = 100;
						zone_brightness_target[10].g = 100;
						zone_brightness_target[10].b = 100;
					} else if (zone_active[9] || zone_active[11]) {
						zone_brightness_target[10].r = adjacent_brightness;
						zone_brightness_target[10].g = adjacent_brightness;
						zone_brightness_target[10].b = adjacent_brightness;
					} else if (zone_active[8] || zone_active[12]) {
						zone_brightness_target[10].r = adjacent2_brightness;
						zone_brightness_target[10].g = adjacent2_brightness;
						zone_brightness_target[10].b = adjacent2_brightness;
					} else if (zone_active[7] || zone_active[1]) {
						zone_brightness_target[10].r = adjacent3_brightness;
						zone_brightness_target[10].g = adjacent3_brightness;
						zone_brightness_target[10].b = adjacent3_brightness;
					} else {
						zone_brightness_target[10].r = 0;
						zone_brightness_target[10].g = 0;
						zone_brightness_target[10].b = 0;
					}
				
					// Adjust Zone 11 Lights.
					if (zone_active[11]) {
						zone_brightness_target[11].r = 100;
						zone_brightness_target[11].g = 100;
						zone_brightness_target[11].b = 100;
					} else if (zone_active[10] || zone_active[12]) {
						zone_brightness_target[11].r = adjacent_brightness;
						zone_brightness_target[11].g = adjacent_brightness;
						zone_brightness_target[11].b = adjacent_brightness;
					} else if (zone_active[9] || zone_active[1]) {
						zone_brightness_target[11].r = adjacent2_brightness;
						zone_brightness_target[11].g = adjacent2_brightness;
						zone_brightness_target[11].b = adjacent2_brightness;
					} else if (zone_active[8] || zone_active[2]) {
						zone_brightness_target[11].r = adjacent3_brightness;
						zone_brightness_target[11].g = adjacent3_brightness;
						zone_brightness_target[11].b = adjacent3_brightness;
					} else {
						zone_brightness_target[11].r = 0;
						zone_brightness_target[11].g = 0;
						zone_brightness_target[11].b = 0;
					}
				
					// Adjust Zone 12 Lights.
					if (zone_active[12]) {
						zone_brightness_target[12].r = 100;
						zone_brightness_target[12].g = 100;
						zone_brightness_target[12].b = 100;
					} else if (zone_active[11] || zone_active[1]) {
						zone_brightness_target[12].r = adjacent_brightness;
						zone_brightness_target[12].g = adjacent_brightness;
						zone_brightness_target[12].b = adjacent_brightness;
					} else if (zone_active[10] || zone_active[2]) {
						zone_brightness_target[12].r = adjacent2_brightness;
						zone_brightness_target[12].g = adjacent2_brightness;
						zone_brightness_target[12].b = adjacent2_brightness;
					} else if (zone_active[9] || zone_active[3]) {
						zone_brightness_target[12].r = adjacent3_brightness;
						zone_brightness_target[12].g = adjacent3_brightness;
						zone_brightness_target[12].b = adjacent3_brightness;
					} else {
						zone_brightness_target[12].r = 0;
						zone_brightness_target[12].g = 0;
						zone_brightness_target[12].b = 0;
					}
			} break;

		// Motion Sensor Deinitialization.
		case ms_deinit: {
				
					ms_timer = 0;			// Turn off the motion sensor timer.
					ms_enable = 0;			// Turn off motion sensor action.

					// Turn all the lights off.
					for (i = 1; i <=12; i++) {
						zone_brightness_target[i].r = 0;
						zone_brightness_target[i].g = 0;
						zone_brightness_target[i].b = 0;
					}
			} break;
	
	}
}

