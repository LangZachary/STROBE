/*****************************************************************************************
 *                                      LIGHTS											 *
 *****************************************************************************************/

/*  Root function for processing lights.
 *  The function checks if the frequency trigger is enabled first.
 *		On frequency trigger a function is ran that turns all the lights off at a set
 *		frequency.  The frequency is set to 100Hz.
 *	The function then checks if dutcycle trigger is enabled.
 *		On duty cycle trigger a function is ran that controls each individual zone and
 *		color of light's brightness.  This is governed by the zone_brightness_current.
 */
void strobe_lights(static unsigned char lights_process)
{

	static unsigned char	lights_enable = 0;
	static unsigned char	lights_shutdown = 0;
	static unsigned char	stage_enable = 0;
	unsigned char i;

	// Variable passed into the function decides which process is completed.
	// 1 - Initialization process for motion sensing mode.
	// 2 - Initialization process for manual.
	// 3 - Initialization process for stages.
	// 3 - General operation.
	// 4 - Lights shutdown.
	switch (lights_process) {

		// Motion Sensing Mode Initialization. (2.063 us)
		case led_ms_init: {
					
							frequency_timer = 1;		// Enable the timers for the lights.
							dutycycle_timer = 1;
		
							lights_enable = 1;			// Enable light action.
					} break;

		// Manual Mode Initialization.  (1.69 us)
		case led_manual_init: {

							for (i = 1; i <= 12; i++) {	// Set all the brightnesses to 0%.
								zone_brightness_target[i].r = 0;
								zone_brightness_target[i].g = 0;
								zone_brightness_target[i].b = 0;
							}

							frequency_timer = 1;		// Enable the timers for the lights.
							dutycycle_timer = 1;
							lights_enable = 1;			// Enable light action.

					} break;

		// Stages Mode Initialization.
		case led_stage_init: {

							frequency_timer = 1;		// Enable the timers for the lights.
							dutycycle_timer = 1;
							lights_enable = 1;			// Enable light action.
							stage_enable = 1;			// Enable automatic light stage changes.

					} break;

		// General Operation.
		case led_run: {
					
							// Check if lights in an enabled mode.
							if (!lights_enable) {
								return;
							}
		
							if (dutycycle_trigger) {  // (20.6 us)
								lights_dutycycle();
								dutycycle_trigger = 0;
							}
		
							if (frequency_trigger) {  // (8.5 us)

								if (stage_enable) {
									lights_frequency_stage(0);
								} else {
									lights_frequency();
								}
								frequency_trigger = 0;
							}

							if (stage_enable) {
								lights_stage(stage_run, 0);
							}
							
					} break;

		// Lights Shutdown.
		case led_deinit: {

							// Set all of the light targets to zero.
							for (i = 1; i <= 12; i++) {
								zone_brightness_target[i].r = 0;
								zone_brightness_target[i].g = 0;
								zone_brightness_target[i].b = 0;
							}
		
							// Keep looping through the normal light cycle until the actual brightness of each
							// light has changed to zero.
							do {
								lights_shutdown = 0;				// Assume the lights are all off.					
		
								
								if (dutycycle_trigger) {			// General PWM operation of the lights.
									lights_dutycycle();
									dutycycle_trigger = 0;
								}
			
								if (frequency_trigger) {
									lights_frequency();
									frequency_trigger = 0;
								}
					
								// Check each of the current light brightnesses. If any are zero set the flag
								// so this process will repeat.
								for (i = 1; i <=12; i++) {
									if (zone_brightness_current[i].r != 0) {
										lights_shutdown = 1;
									}
									if (zone_brightness_current[i].g != 0) {
										lights_shutdown = 1;
									}
									if (zone_brightness_current[i].b != 0) {
										lights_shutdown = 1;
									}
								}
							} while (lights_shutdown);
		
							// When all of the lights are off, turn off the light timers and disable
							// general light operation in this function.
							frequency_timer = 0;
							dutycycle_timer = 0;
							lights_enable = 0;
							stage_enable = 0;

					} break;				
	}


}


void lights_stage(static unsigned char stage_process, static unsigned char slot)
{
	static unsigned char 		i = 0;
	static unsigned int 		stage_count_next = 0;	// Length of the next delay before a stage switch.
	static unsigned long		stage_start_add = 0;	// Starting address of the current stage playing.
	static unsigned long		stage_current_add = 0;	// Address of the current stages playing.
	static unsigned char 		stage_total = 0;		// Total stages in the current show.
	static unsigned char 		stage_current = 0;		// Current stage of the show.
	static unsigned char		stage_data[128];		// Array to store a block of stage data.
	static unsigned char		stage_odd = 0;			// Keeps track of whether the stage number is odd or even.
	static unsigned float		stage_fade_speed = 0;	// Percent change of each zone.
	static unsigned int			stage_fade_steps_next = 0; // The number of steps in the next fade sequence.
	static unsigned char		stage_fade_level = 0;	// Level of fade speed desired for next step.
	static unsigned char		stage_hold_enable = 0;	// Ready to execute code for a hold.
	static unsigned char		stage_fade_enable = 0;	// Ready to execute code for a fade.
	unsigned char *ptr;


	switch (stage_process) {

		// Stage initialization.
		case stage_init: {	// Initialize variables.
							stage_odd = 0;
							stage_current = 0;

							// Read the first stages information.
							switch (stage_save_slot) {
								case 1:	stage_start_add = 0x12000;
										break;
								case 2: stage_start_add = 0x12800;
										break;
								case 3: stage_start_add = 0x13000;
										break;
								case 4: stage_start_add = 0x13800;
										break;
								case 5: stage_start_add = 0x14000;
										break;
								case 6: stage_start_add = 0x17000;
										break;
								case 7: stage_start_add = 0x1A000;
										break;
								case 8: stage_start_add = 0x1D000;
										break;
							}

							stage_current_add = stage_start_add;
							mem_read(stage_current_add, &stage_data[0], 128);

							// Load the next stage brightness target.
							for (i = 0; i < 12; i++) {
								zone_brightness_target_next[i+1].r = stage_data[red1+i];
								zone_brightness_target_next[i+1].g = stage_data[green1+i];
								zone_brightness_target_next[i+1].b = stage_data[blue1+i];
							}	

				//			strobe_lights(led_run);				// Check the lights.

							// Load the total stages in this show.
							stage_total = stage_data[total_stages];

							// Load the next stage delay.
							stage_count_next = stage_data[hold_time1h];
							stage_count_next = stage_count << 8;
							stage_count_next = stage_count + (int)stage_data[hold_time1l];

							// Load the percent change of each step based on the chosen fade time.
							switch (stage_data[fade_time1]){
								case 0: stage_fade_speed = fade_speed0;		// 5.0s
										stage_fade_steps_next = fade_steps0;
										break;
								case 1: stage_fade_speed = fade_speed1;		// 4.8s
										stage_fade_steps_next = fade_steps1;
										break;
								case 2: stage_fade_speed = fade_speed2;		// 4.6s
										stage_fade_steps_next = fade_steps2;
										break;
								case 3: stage_fade_speed = fade_speed3;		// 4.4s
										stage_fade_steps_next = fade_steps3;
										break;
								case 4: stage_fade_speed = fade_speed4;		// 4.2s
										stage_fade_steps_next = fade_steps4;
										break;
								case 5: stage_fade_speed = fade_speed5;		// 4.0s
										stage_fade_steps_next = fade_steps5;
										break;
								case 6: stage_fade_speed = fade_speed6;		// 3.8s
										stage_fade_steps_next = fade_steps6;
										break;
								case 7: stage_fade_speed = fade_speed7;		// 3.6s
										stage_fade_steps_next = fade_steps7;
										break;
								case 8: stage_fade_speed = fade_speed8;		// 3.4s
										stage_fade_steps_next = fade_steps8;
										break;
								case 9: stage_fade_speed = fade_speed9;		// 3.2s
										stage_fade_steps_next = fade_steps9;
										break;
								case 10: stage_fade_speed = fade_speed10;	// 3.0s
										stage_fade_steps_next = fade_steps10;
										break;
								case 11: stage_fade_speed = fade_speed11;	// 2.9s
										stage_fade_steps_next = fade_steps11;
										break;
								case 12: stage_fade_speed = fade_speed12;	// 2.8s
										stage_fade_steps_next = fade_steps12;
										break;
								case 13: stage_fade_speed = fade_speed13;	// 2.7s
										stage_fade_steps_next = fade_steps13;
										break;
								case 14: stage_fade_speed = fade_speed14;	// 2.6s
										stage_fade_steps_next = fade_steps14;
										break;
								case 15: stage_fade_speed = fade_speed15;	// 2.5s
										stage_fade_steps_next = fade_steps15;
										break;
								case 16: stage_fade_speed = fade_speed16;	// 2.4s
										stage_fade_steps_next = fade_steps16;
										break;
								case 17: stage_fade_speed = fade_speed17;	// 2.3s
										stage_fade_steps_next = fade_steps17;
										break;
								case 18: stage_fade_speed = fade_speed18;	// 2.2s
										stage_fade_steps_next = fade_steps18;
										break;
								case 19: stage_fade_speed = fade_speed19;	// 2.1s
										stage_fade_steps_next = fade_steps19;
										break;
								case 20: stage_fade_speed = fade_speed20;	// 2s
										stage_fade_steps_next = fade_steps20;
										break;
								case 21: stage_fade_speed = fade_speed21;	// 1.9s
										stage_fade_steps_next = fade_steps21;
										break;
								case 22: stage_fade_speed = fade_speed22;	// 1.8s
										stage_fade_steps_next = fade_steps22;
										break;
								case 23: stage_fade_speed = fade_speed23;	// 1.7s
										stage_fade_steps_next = fade_steps23;
										break;
								case 24: stage_fade_speed = fade_speed24;	// 1.6s
										stage_fade_steps_next = fade_steps24;
										break;
								case 25: stage_fade_speed = fade_speed25;	// 1.5s
										stage_fade_steps_next = fade_steps25;
										break;
								case 26: stage_fade_speed = fade_speed26;	// 1.4s
										stage_fade_steps_next = fade_steps26;
										break;
								case 27: stage_fade_speed = fade_speed27;	// 1.3s
										stage_fade_steps_next = fade_steps27;
										break;
								case 28: stage_fade_speed = fade_speed28;	// 1.2s
										stage_fade_steps_next = fade_steps28;
										break;
								case 29: stage_fade_speed = fade_speed29;	// 1.1s
										stage_fade_steps_next = fade_steps29;
										break;
								case 30: stage_fade_speed = fade_speed30;	// 1.0s
										stage_fade_steps_next = fade_steps30;
										break;
								case 31: stage_fade_speed = fade_speed31;	// 0.95s
										stage_fade_steps_next = fade_steps31;
										break;
								case 32: stage_fade_speed = fade_speed32;	// 0.9s
										stage_fade_steps_next = fade_steps32;
										break;
								case 33: stage_fade_speed = fade_speed33;	// 0.85s
										stage_fade_steps_next = fade_steps33;
										break;
								case 34: stage_fade_speed = fade_speed34;	// 0.8s
										stage_fade_steps_next = fade_steps34;
										break;
								case 35: stage_fade_speed = fade_speed35;	// 0.75s
										stage_fade_steps_next = fade_steps35;
										break;
								case 36: stage_fade_speed = fade_speed36;	// 0.7s
										stage_fade_steps_next = fade_steps36;
										break;
								case 37: stage_fade_speed = fade_speed37;	// 0.65s
										stage_fade_steps_next = fade_steps37;
										break;
								case 38: stage_fade_speed = fade_speed38;	// 0.6s
										stage_fade_steps_next = fade_steps38;
										break;
								case 39: stage_fade_speed = fade_speed39;	// 0.55s
										stage_fade_steps_next = fade_steps39;
										break;
								case 40: stage_fade_speed = fade_speed40;	// 0.5s
										stage_fade_steps_next = fade_steps40;
										break;
								case 41: stage_fade_speed = fade_speed41;	// 0.45s
										stage_fade_steps_next = fade_steps41;
										break;
								case 42: stage_fade_speed = fade_speed42;	// 0.4s
										stage_fade_steps_next = fade_steps42;
										break;
								case 43: stage_fade_speed = fade_speed43;	// 0.35s
										stage_fade_steps_next = fade_steps43;
										break;
								case 44: stage_fade_speed = fade_speed44;	// 0.3s
										stage_fade_steps_next = fade_steps44;
										break;
								case 45: stage_fade_speed = fade_speed45;	// 0.25s
										stage_fade_steps_next = fade_steps45;
										break;
								case 46: stage_fade_speed = fade_speed46;	// 0.2s
										stage_fade_steps_next = fade_steps46;
										break;
								case 47: stage_fade_speed = fade_speed47;	// 0.15s
										stage_fade_steps_next = fade_steps47;
										break;
								case 48: stage_fade_speed = fade_speed48;	// 0.1s
										stage_fade_steps_next = fade_steps48;
										break;
								case 49: stage_fade_speed = fade_speed49;	// 0.05s
										stage_fade_steps_next = fade_steps49;
										break;
								case 50: stage_fade_speed = fade_speed50;	// 0s
										stage_fade_steps_next = fade_steps50;
										break;
							}
								
							for (i = 1; i <= 12; i++) {
		
								// Reset the current sum of steps to the current brightness.
								zone_brightness_fade_stepsum[i].r = zone_brightness_current[i].r;
								zone_brightness_fade_stepsum[i].g = zone_brightness_current[i].g;
								zone_brightness_fade_stepsum[i].b = zone_brightness_current[i].b;

								// Save the step size for each zone.
								zone_brightness_fade_stepsize[i].r = ((int)zone_brightness_target_next[i].r - (int)zone_brightness_current[i].r) * stage_fade_speed;
								zone_brightness_fade_stepsize[i].g = ((int)zone_brightness_target_next[i].g - (int)zone_brightness_current[i].g) * stage_fade_speed;
								zone_brightness_fade_stepsize[i].b = ((int)zone_brightness_target_next[i].b - (int)zone_brightness_current[i].b) * stage_fade_speed;
							}

		//					strobe_lights(led_run);				// Check the lights.

							for (i = 1; i <= 12; i++) {

								// Set the next targt brightness and start the fade process.
								zone_brightness_target[i] = zone_brightness_target_next[i];
							}
			
							// Reset the fade steps taken.
							stage_fade_steps = stage_fade_steps_next;

							// Enable the Hold code in the main routine.
							stage_hold_enable = 1;
							stage_fade_enable = 0;

							// Turn the lights on.
							strobe_lights(led_stage_init);		

						} break;

		case stage_save_init:	{
									// Point to the initial stage.
									switch (stage_save_slot) {
										case 1:	stage_start_add = 0x12000;
												break;
										case 2: stage_start_add = 0x12800;
												break;
										case 3: stage_start_add = 0x13000;
												break;
										case 4: stage_start_add = 0x13800;
												break;
										case 5: stage_start_add = 0x14000;
												break;
										case 6: stage_start_add = 0x17000;
												break;
										case 7: stage_start_add = 0x1A000;
												break;
										case 8: stage_start_add = 0x1D000;
												break;
									}
										stage_current_add = stage_start_add;

										// Read in the current name saved.
										mem_read(stage_current_add + 0x10, &stage_data[0x10], 16);

										// Set the initial stage information.
										stage_save_count = 1;
										stage_current = 1;
										stage_total = 1;
										stage_odd = 1;
										zone_select = 0;

										// Turn on the lights
										strobe_lights(led_manual_init);							

										} break;								

		// Stage Run
		case stage_run:	{
							// Hold Code.
							if (stage_hold_enable) {
							
								// Don't start until the fading is finished.
								if (stage_fade_steps > 0) {
									break;
								}

								// Force the current brightnesses to be equal to the target for error resolution.
								for (i = 1; i <= 12; i++) {
									zone_brightness_current[i] = zone_brightness_target[i];
								}

								// Check the lights.
								if (dutycycle_trigger) {  // (20.6 us)
									lights_dutycycle();
									dutycycle_trigger = 0;
								}
			
								if (frequency_trigger) {  // (8.5 us)
									lights_frequency_stage(0);
									frequency_trigger = 0;
								}

								// Increment the current stage.
								stage_current++;	
	
								// Toggle the stage odd.
								stage_odd = !stage_odd;
	
								// Start the Hold process.
								stage_count = stage_count_next;
								stage_timer = 1;
								stage_ready = 0;
							
								// Not on the last stage.
								if (stage_current < stage_total) {
									
									if (stage_odd) {
		
										// Load the next stage brightness target.
										for (i = 0; i < 12; i++) {
											zone_brightness_target_next[i+1].r = stage_data[red2+i];
											zone_brightness_target_next[i+1].g = stage_data[green2+i];
											zone_brightness_target_next[i+1].b = stage_data[blue2+i];
										}
	
										// Load the next stage delay.
										stage_count_next = stage_data[hold_time2h];
										stage_count_next = stage_count_next << 8;
										stage_count_next = stage_count_next + (int)stage_data[hold_time2l];
	
										// Load the stage fade level.
										stage_fade_level = stage_data[fade_time2];
	
									} else {
		
										// Read the next two stages in.
										stage_current_add = stage_current_add + 0x80;
										mem_read(stage_current_add, &stage_data[0], 128);
										
										// Load the next stage brightness target.
										for (i = 0; i < 12; i++) {
											zone_brightness_target_next[i+1].r = stage_data[red1+i];
											zone_brightness_target_next[i+1].g = stage_data[green1+i];
											zone_brightness_target_next[i+1].b = stage_data[blue1+i];
										}
	
										// Load the next stage delay.
										stage_count_next = stage_data[hold_time1h];
										stage_count_next = stage_count << 8;
										stage_count_next = stage_count + (int)stage_data[hold_time1l];
	
										// Load the stage fade level.
										stage_fade_level = stage_data[fade_time1];									
									}
	
								// On the last stage.
								} else {
									
									// Reset the stage counting variables.
									stage_current = 0;
									stage_odd = 0;
	
									// Read the first stages in.
									stage_current_add = stage_start_add;
									mem_read(stage_current_add, &stage_data[0], 128);
	
									// Load the next stage brightness target.
									for (i = 0; i < 12; i++) {
										zone_brightness_target_next[i+1].r = stage_data[red1+i];
										zone_brightness_target_next[i+1].g = stage_data[green1+i];
										zone_brightness_target_next[i+1].b = stage_data[blue1+i];
									}
	
									// Load the next stage delay.
									stage_count_next = stage_data[hold_time1h];
									stage_count_next = stage_count_next << 8;
									stage_count_next = stage_count_next + (int)stage_data[hold_time1l];
	
									// Load the stage fade level.
									stage_fade_level = stage_data[fade_time1];
								}
	
								// Check the lights.
								if (dutycycle_trigger) {  // (20.6 us)
									lights_dutycycle();
									dutycycle_trigger = 0;
								}
			
								if (frequency_trigger) {  // (8.5 us)
									lights_frequency_stage(0);
									frequency_trigger = 0;
								}

								// Load the percent change of each step based on the chosen fade time.
								switch (stage_fade_level){
									case 0: stage_fade_speed = fade_speed0;		// 5.0s
											stage_fade_steps_next = fade_steps0;
											break;
									case 1: stage_fade_speed = fade_speed1;		// 4.8s
											stage_fade_steps_next = fade_steps1;
											break;
									case 2: stage_fade_speed = fade_speed2;		// 4.6s
											stage_fade_steps_next = fade_steps2;
											break;
									case 3: stage_fade_speed = fade_speed3;		// 4.4s
											stage_fade_steps_next = fade_steps3;
											break;
									case 4: stage_fade_speed = fade_speed4;		// 4.2s
											stage_fade_steps_next = fade_steps4;
											break;
									case 5: stage_fade_speed = fade_speed5;		// 4.0s
											stage_fade_steps_next = fade_steps5;
											break;
									case 6: stage_fade_speed = fade_speed6;		// 3.8s
											stage_fade_steps_next = fade_steps6;
											break;
									case 7: stage_fade_speed = fade_speed7;		// 3.6s
											stage_fade_steps_next = fade_steps7;
											break;
									case 8: stage_fade_speed = fade_speed8;		// 3.4s
											stage_fade_steps_next = fade_steps8;
											break;
									case 9: stage_fade_speed = fade_speed9;		// 3.2s
											stage_fade_steps_next = fade_steps9;
											break;
									case 10: stage_fade_speed = fade_speed10;	// 3.0s
											stage_fade_steps_next = fade_steps10;
											break;
									case 11: stage_fade_speed = fade_speed11;	// 2.9s
											stage_fade_steps_next = fade_steps11;
											break;
									case 12: stage_fade_speed = fade_speed12;	// 2.8s
											stage_fade_steps_next = fade_steps12;
											break;
									case 13: stage_fade_speed = fade_speed13;	// 2.7s
											stage_fade_steps_next = fade_steps13;
											break;
									case 14: stage_fade_speed = fade_speed14;	// 2.6s
											stage_fade_steps_next = fade_steps14;
											break;
									case 15: stage_fade_speed = fade_speed15;	// 2.5s
											stage_fade_steps_next = fade_steps15;
											break;
									case 16: stage_fade_speed = fade_speed16;	// 2.4s
											stage_fade_steps_next = fade_steps16;
											break;
									case 17: stage_fade_speed = fade_speed17;	// 2.3s
											stage_fade_steps_next = fade_steps17;
											break;
									case 18: stage_fade_speed = fade_speed18;	// 2.2s
											stage_fade_steps_next = fade_steps18;
											break;
									case 19: stage_fade_speed = fade_speed19;	// 2.1s
											stage_fade_steps_next = fade_steps19;
											break;
									case 20: stage_fade_speed = fade_speed20;	// 2s
											stage_fade_steps_next = fade_steps20;
											break;
									case 21: stage_fade_speed = fade_speed21;	// 1.9s
											stage_fade_steps_next = fade_steps21;
											break;
									case 22: stage_fade_speed = fade_speed22;	// 1.8s
											stage_fade_steps_next = fade_steps22;
											break;
									case 23: stage_fade_speed = fade_speed23;	// 1.7s
											stage_fade_steps_next = fade_steps23;
											break;
									case 24: stage_fade_speed = fade_speed24;	// 1.6s
											stage_fade_steps_next = fade_steps24;
											break;
									case 25: stage_fade_speed = fade_speed25;	// 1.5s
											stage_fade_steps_next = fade_steps25;
											break;
									case 26: stage_fade_speed = fade_speed26;	// 1.4s
											stage_fade_steps_next = fade_steps26;
											break;
									case 27: stage_fade_speed = fade_speed27;	// 1.3s
											stage_fade_steps_next = fade_steps27;
											break;
									case 28: stage_fade_speed = fade_speed28;	// 1.2s
											stage_fade_steps_next = fade_steps28;
											break;
									case 29: stage_fade_speed = fade_speed29;	// 1.1s
											stage_fade_steps_next = fade_steps29;
											break;
									case 30: stage_fade_speed = fade_speed30;	// 1.0s
											stage_fade_steps_next = fade_steps30;
											break;
									case 31: stage_fade_speed = fade_speed31;	// 0.95s
											stage_fade_steps_next = fade_steps31;
											break;
									case 32: stage_fade_speed = fade_speed32;	// 0.9s
											stage_fade_steps_next = fade_steps32;
											break;
									case 33: stage_fade_speed = fade_speed33;	// 0.85s
											stage_fade_steps_next = fade_steps33;
											break;
									case 34: stage_fade_speed = fade_speed34;	// 0.8s
											stage_fade_steps_next = fade_steps34;
											break;
									case 35: stage_fade_speed = fade_speed35;	// 0.75s
											stage_fade_steps_next = fade_steps35;
											break;
									case 36: stage_fade_speed = fade_speed36;	// 0.7s
											stage_fade_steps_next = fade_steps36;
											break;
									case 37: stage_fade_speed = fade_speed37;	// 0.65s
											stage_fade_steps_next = fade_steps37;
											break;
									case 38: stage_fade_speed = fade_speed38;	// 0.6s
											stage_fade_steps_next = fade_steps38;
											break;
									case 39: stage_fade_speed = fade_speed39;	// 0.55s
											stage_fade_steps_next = fade_steps39;
											break;
									case 40: stage_fade_speed = fade_speed40;	// 0.5s
											stage_fade_steps_next = fade_steps40;
											break;
									case 41: stage_fade_speed = fade_speed41;	// 0.45s
											stage_fade_steps_next = fade_steps41;
											break;
									case 42: stage_fade_speed = fade_speed42;	// 0.4s
											stage_fade_steps_next = fade_steps42;
											break;
									case 43: stage_fade_speed = fade_speed43;	// 0.35s
											stage_fade_steps_next = fade_steps43;
											break;
									case 44: stage_fade_speed = fade_speed44;	// 0.3s
											stage_fade_steps_next = fade_steps44;
											break;
									case 45: stage_fade_speed = fade_speed45;	// 0.25s
											stage_fade_steps_next = fade_steps45;
											break;
									case 46: stage_fade_speed = fade_speed46;	// 0.2s
											stage_fade_steps_next = fade_steps46;
											break;
									case 47: stage_fade_speed = fade_speed47;	// 0.15s
											stage_fade_steps_next = fade_steps47;
											break;
									case 48: stage_fade_speed = fade_speed48;	// 0.1s
											stage_fade_steps_next = fade_steps48;
											break;
									case 49: stage_fade_speed = fade_speed49;	// 0.05s
											stage_fade_steps_next = fade_steps49;
											break;
									case 50: stage_fade_speed = fade_speed50;	// 0s
											stage_fade_steps_next = fade_steps50;
											break;
								}									
		
								for (i = 1; i <= 12; i++) {
			
									// Reset the current sum of steps to the current brightness.
									zone_brightness_fade_stepsum[i].r = zone_brightness_current[i].r;
									zone_brightness_fade_stepsum[i].g = zone_brightness_current[i].g;
									zone_brightness_fade_stepsum[i].b = zone_brightness_current[i].b;
	
									// Save the step size for each zone.
									zone_brightness_fade_stepsize[i].r = ((int)zone_brightness_target_next[i].r - (int)zone_brightness_current[i].r) * stage_fade_speed;
									zone_brightness_fade_stepsize[i].g = ((int)zone_brightness_target_next[i].g - (int)zone_brightness_current[i].g) * stage_fade_speed;
									zone_brightness_fade_stepsize[i].b = ((int)zone_brightness_target_next[i].b - (int)zone_brightness_current[i].b) * stage_fade_speed;
								}

								// Check the lights.
								if (dutycycle_trigger) {  // (20.6 us)
									lights_dutycycle();
									dutycycle_trigger = 0;
								}
			
								if (frequency_trigger) {  // (8.5 us)
									lights_frequency_stage(0);
									frequency_trigger = 0;
								}

								// Enable Fade Code.
								stage_fade_enable = 1;
								stage_hold_enable = 0;
							}

							// Fade Code.
							if (stage_fade_enable) {
								
								// Wait until the hold stage is finished.
								if (!stage_ready) {
									break;
								}

								for (i = 1; i <= 12; i++) {
		
									// Start the Fading Process.
									zone_brightness_target[i] = zone_brightness_target_next[i];
								}

								// Enable fading in the lights routine and set how many times it should change.
								stage_fade_steps = stage_fade_steps_next;

								// Enable Hold Code.
								stage_hold_enable = 1;
								stage_fade_enable = 0;

							}
	
						} break;

		case stage_save_run:	{	switch (oled.menu) {

										// Hit Next		
										case strobe_long_new2c:		
										case strobe_short_new2c:	// If the user is at the max stage, do not move.
																	if (stage_save_slot < 5) {
																		if (stage_current == 32) {
																			break;
																		}
																	} else if (stage_current == 192) {
																			break;
																	}

																	// On an odd stage.
																	if (stage_odd) {

																		// Save the current brightness in the first position in the data array.
																		for (i = 0; i < 12; i++) {
																			stage_data[red1+i] = zone_brightness_current[i+1].r;
																			stage_data[green1+i] = zone_brightness_current[i+1].g;
																			stage_data[blue1+i] = zone_brightness_current[i+1].b;
																		}
														
																		strobe_lights(led_run);				// Check the lights.

																		// Save the hold time and fade time.
																		stage_data[hold_time1h] = adc_hold_time >> 8;
																		stage_data[hold_time1l] = adc_hold_time;
																		stage_data[fade_time1] = adc_fade_time;
	
																		// Load the next stages data if this saving session has previously saved data there
																		// otherwise assume it is the same as the current zone.
																		if (stage_current < stage_total) {
																			
																			// Load the current brightness from the next position in the data array.
																			for (i = 0; i < 12; i++) {
																				zone_brightness_target[i+1].r = stage_data[red2+i];
																				zone_brightness_target[i+1].g = stage_data[green2+i];
																				zone_brightness_target[i+1].b = stage_data[blue2+i];
																			}

																			// Load the hold time and fade time.
																			adc_hold_time = stage_data[hold_time2h];
																			adc_hold_time = adc_hold_time << 8;
																			adc_hold_time = adc_hold_time + (int)stage_data[hold_time2l];
																			adc_fade_time = stage_data[fade_time2];
																		} else {
																			stage_total++;
																		}
																	
																	} else { // On an even stage
																		// Save the current brightness in the second position in the data array.
																		for (i = 0; i < 12; i++) {
																			stage_data[red2+i] = zone_brightness_current[i+1].r;
																			stage_data[green2+i] = zone_brightness_current[i+1].g;
																			stage_data[blue2+i] = zone_brightness_current[i+1].b;
																		}
														
																		strobe_lights(led_run);				// Check the lights.

																		// Save the hold time and fade time.
																		stage_data[hold_time2h] = adc_hold_time >> 8;
																		stage_data[hold_time2l] = adc_hold_time;
																		stage_data[fade_time2] = adc_fade_time;

																		mem_erase(stage_current_add, stage_current_add + 0x80);
																		// Write the data to ROM.
																		mem_write(stage_current_add, &stage_data[0], 127);
																		
																		// Increment the memory location
																		stage_current_add = stage_current_add + 0x80;

																		// Load the next stages data if this saving session has previously saved data there
																		// otherwise assume it is the same as the current zone.
																		if (stage_current < stage_total) {

																			// Read in the new data.
																			mem_read(stage_current_add, &stage_data[0], 128);
																		
																			// Load the current brightness from the next position in the data array.
																			for (i = 0; i < 12; i++) {
																				zone_brightness_target[i+1].r = stage_data[red1+i];
																				zone_brightness_target[i+1].g = stage_data[green1+i];
																				zone_brightness_target[i+1].b = stage_data[blue1+i];
																			}

																			// Load the hold time and fade time.
																			adc_hold_time = stage_data[hold_time1h];
																			adc_hold_time = adc_hold_time << 8;
																			adc_hold_time = adc_hold_time + (int)stage_data[hold_time1l];
																			adc_fade_time = stage_data[fade_time1];

																		} else {
																			stage_total++;
																		}

																	}

																	// Toggle stage_odd and increase the current stage_counter.
																	stage_odd = !stage_odd;
																	stage_current++;
																	stage_save_count = stage_current;

																	break;

										// Hit Back	
										case strobe_long_new2d:				
										case strobe_short_new2d:	// If the user is at the first stage, do nothing.
																	if (stage_current == 1) {
																		break;
																	}

																	// On an even stage
																	if (!stage_odd) {

																		// Save the current brightness in the second position in the data array.
																		for (i = 0; i < 12; i++) {
																			stage_data[red2+i] = zone_brightness_current[i+1].r;
																			stage_data[green2+i] = zone_brightness_current[i+1].g;
																			stage_data[blue2+i] = zone_brightness_current[i+1].b;
																		}
														
																		strobe_lights(led_run);				// Check the lights.

																		// Save the hold time and fade time.
																		stage_data[hold_time2h] = adc_hold_time >> 8;
																		stage_data[hold_time2l] = adc_hold_time;
																		stage_data[fade_time2] = adc_fade_time;
	
																		// Load the current brightness from the first position in the data array.
																		for (i = 0; i < 12; i++) {
																			zone_brightness_target[i+1].r = stage_data[red1+i];
																			zone_brightness_target[i+1].g = stage_data[green1+i];
																			zone_brightness_target[i+1].b = stage_data[blue1+i];
																		}

																		// Load the hold time and fade time.
																		adc_hold_time = stage_data[hold_time1h];
																		adc_hold_time = adc_hold_time << 8;
																		adc_hold_time = adc_hold_time + (int)stage_data[hold_time1l];
																	
																	} else { // On an odd stage,
																		// Save the current brightness in the first position in the data array.
																		for (i = 0; i < 12; i++) {
																			stage_data[red1+i] = zone_brightness_current[i+1].r;
																			stage_data[green1+i] = zone_brightness_current[i+1].g;
																			stage_data[blue1+i] = zone_brightness_current[i+1].b;
																		}
														
																		strobe_lights(led_run);				// Check the lights.

																		// Save the hold time and fade time.
																		stage_data[hold_time1h] = adc_hold_time >> 8;
																		stage_data[hold_time1l] = adc_hold_time;
																		stage_data[fade_time1] = adc_fade_time;

																		mem_erase(stage_current_add, stage_current_add + 0x80);
																		// Write the data to ROM.
																		mem_write(stage_current_add, &stage_data[0], 127);
																		
																		// Decrement the memory location
																		stage_current_add = stage_current_add - 0x80;

\																		// Load the new data.
																		mem_read(stage_current_add, &stage_data[0], 128);
																		
																		// Load the current brightness from the next position in the data array.
																		for (i = 0; i < 12; i++) {
																			zone_brightness_target[i+1].r = stage_data[red2+i];
																			zone_brightness_target[i+1].g = stage_data[green2+i];
																			zone_brightness_target[i+1].b = stage_data[blue2+i];
																		}

																		// Load the hold time and fade time.
																		adc_hold_time = stage_data[hold_time2h];
																		adc_hold_time = adc_hold_time << 8;
																		adc_hold_time = adc_hold_time + (int)stage_data[hold_time2l];
																		adc_fade_time = stage_data[fade_time2];

																		}

																		// Toggle stage_odd and decrease the current stage_counter.
																		stage_odd = !stage_odd;
																		stage_current--;
																		stage_save_count = stage_current;


																	break;
										// Hit Done
										case strobe_long_new2e:				
										case strobe_short_new2e:	// If the user hasn't saved any stages, exit to the strobe short main menu.
																	if (stage_total == 1) {

																		// Turn off the lights.
																		strobe_lights(led_deinit);
																		
																		// Reset all of the variables.
																		stage_save_count = 1;
																		stage_current = 1;
																		stage_total = 1;
																		stage_odd = 1;

																		// Go to the short main menu.
																		oled.menu = strobe_short1a;
																		strobe_oled(oled_menu, 0, 0);
																		break;
																	}

																	// On an even stage
																	if (!stage_odd) {

																		// Save the current brightness in the second position in the data array.
																		for (i = 0; i < 12; i++) {
																			stage_data[red2+i] = zone_brightness_current[i+1].r;
																			stage_data[green2+i] = zone_brightness_current[i+1].g;
																			stage_data[blue2+i] = zone_brightness_current[i+1].b;
																		}
														
																		// Save the hold time and fade time.
																		stage_data[hold_time2h] = adc_hold_time >> 8;
																		stage_data[hold_time2l] = adc_hold_time;
																		stage_data[fade_time2] = adc_fade_time;
																
																	} else { // On an odd stage,
																		// Save the current brightness in the first position in the data array.
																		for (i = 0; i < 12; i++) {
																			stage_data[red1+i] = zone_brightness_current[i+1].r;
																			stage_data[green1+i] = zone_brightness_current[i+1].g;
																			stage_data[blue1+i] = zone_brightness_current[i+1].b;
																		}
														
																		// Save the hold time and fade time.
																		stage_data[hold_time1h] = adc_hold_time >> 8;
																		stage_data[hold_time1l] = adc_hold_time;
																		stage_data[fade_time1] = adc_fade_time;
																	}

																	// Turn off the lights.
																	strobe_lights(led_deinit);

																	mem_erase(stage_current_add, stage_current_add + 0x80);
																	// Write the data to ROM.
																	mem_write(stage_current_add, &stage_data[0], 127);
																		
																	// Go to the first memory location.
																	stage_current_add = stage_start_add;

\																	// Load the new data.
																	mem_read(stage_current_add, &stage_data[0], 128);
																		
																	// Save the total stages in the register.
																	stage_data[0] = stage_total;

																	break;
										}																							

							} break;

		case stage_deinit:	{	// Store the name typed in into the data array.
								for (i = 0; i < 14; i++) {
									stage_data[i + 16] = name[i];
								}

								mem_erase(stage_current_add, stage_current_add + 0x80);
								// Save the stage data and name data.
								mem_write(stage_current_add, &stage_data[0], 127);

								// Reset any variables that need resetting.

							} break;					

	}
}

// This function controls the Strobe Light in the Strobe Menu.
void lights_strobelight(void)
{

	static unsigned char	lights_on = 0;	// Keeps track of whether the lights are currently on or off.
	static unsigned char	strobelight_enable = 0;	// Turns on and off the Strobe Light.	
	static unsigned char i;
	static unsigned char button;

	// Set default values for the strobe light speed.
	strobelight_time_off = 500;
	strobelight_time_on = 500;

	// Activate the dials to change the time off and time on.
	strobe_adc(adc_dual_init);

	// Enable the strobe light.
	strobelight_enable = 1;

	// Start with the light off.
	strobelight_count = strobelight_time_off;
	strobelight_timer = 1;
	strobelight_ready = 0;
	lights_on = 0;

	// Turn all the lights off.
	LATBbits.LIGHTS = 0b0;
	LATDbits.LIGHTS = 0b00000000;
	LATEbits.LIGHTSa = 0b00;
	LATEbits.LIGHTSb = 0b00000;
	LATFbits.LIGHTS = 0b000000;
	LATGbits.LIGHTS = 0b0000;
	LATHbits.LIGHTSa = 0b0000;
	LATHbits.LIGHTSb = 0b00;
	LATJbits.LIGHTS = 0b0000;

	do {

		// Check the dials.
		strobe_adc(adc_dual_run);

		// Change the OLED display if necessary.
		strobe_oled(oled_run, 0, 0);

		// Change the lights when they are ready.
		if (strobelight_ready) {

			// Lights are currently on.
			if (lights_on) {

				// Start the delay for the lights off.
				strobelight_count = strobelight_time_off;

				// Turn all the lights off.
				LATBbits.LIGHTS = 0b0;
				LATDbits.LIGHTS = 0b00000000;
				LATEbits.LIGHTSa = 0b00;
				LATEbits.LIGHTSb = 0b00000;
				LATFbits.LIGHTS = 0b000000;
				LATGbits.LIGHTS = 0b0000;
				LATHbits.LIGHTSa = 0b0000;
				LATHbits.LIGHTSb = 0b00;
				LATJbits.LIGHTS = 0b0000;
			
				lights_on = 0;
			
			// Lights are currently off.
			} else {

				// Start the delay for the lights on.
				strobelight_count = strobelight_time_on;

				// Turn all the lights off.
				LATBbits.LIGHTS = 0b1;
				LATDbits.LIGHTS = 0b11111111;
				LATEbits.LIGHTSa = 0b11;
				LATEbits.LIGHTSb = 0b11111;
				LATFbits.LIGHTS = 0b111111;
				LATGbits.LIGHTS = 0b1111;
				LATHbits.LIGHTSa = 0b1111;
				LATHbits.LIGHTSb = 0b11;
				LATJbits.LIGHTS = 0b1111;
			
				lights_on = 1;
			}

			strobelight_ready = 0;
		}

		// Check for the user hitting the menu button.
		if (buttons_check() == button_menu_pressed) {
			
			// End the strobelight routine.
			
			// Turn all the lights off.
			LATBbits.LIGHTS = 0b0;
			LATDbits.LIGHTS = 0b00000000;
			LATEbits.LIGHTSa = 0b00;
			LATEbits.LIGHTSb = 0b00000;
			LATFbits.LIGHTS = 0b000000;
			LATGbits.LIGHTS = 0b0000;
			LATHbits.LIGHTSa = 0b0000;
			LATHbits.LIGHTSb = 0b00;
			LATJbits.LIGHTS = 0b0000;

			// Disable the strobe light.
			strobelight_enable = 0;

			// Deactivate the dials.
			strobe_adc(adc_dual_deinit);

			// Change the menu.
			oled.menu = strobe_menu1a;
			strobe_oled(oled_menu, 0, 0);
			oled.menu = strobe_menu1c;
			strobe_oled(oled_menu, 0, 0);

			// Turn off the timer.
			strobelight_timer = 0;
			strobelight_ready = 0;
		}

	}while (strobelight_enable);
			
}								



void lights_frequency_stage(unsigned char reset_zone)
{
	static unsigned char current_zone = 1;
	static unsigned char i;

	// Cycle through all twelve zones.
	if (current_zone == 12) {
		current_zone = 1;

		// Sync the clocks.
		TMR0H = frequency_high;	
		TMR0L = frequency_low;
	
		TMR1H = dutycycle_high;	
		TMR1L = dutycycle_low;

		// Count down the fade step. Adjust the new brightness for this step.
		if (stage_fade_steps > 0) {
			stage_fade_steps--;
		}

	} else {
		current_zone++;
	}

	// Turn off the lights in the current zone.
	switch (current_zone) {
		
		// ZONE 1 //
		case 1:		z1r = 0;
					z1g = 0;
					z1b = 0;
					break;

		// ZONE 2 //
		case 2:		z2r = 0;
					z2g = 0;
					z2b = 0;
					break;

		// ZONE 3 //
		case 3:		z3r = 0;
					z3g = 0;
					z3b = 0;
					break;

		// ZONE 4 //
		case 4:		z4r = 0;
					z4g = 0;
					z4b = 0;
					break;

		// ZONE 5 //
		case 5:		z5r = 0;
					z5g = 0;
					z5b = 0;
					break;

		// ZONE 6 //
		case 6:		z6r = 0;
					z6g = 0;
					z6b = 0;
					break;

		// ZONE 7 //
		case 7:		z7r = 0;
					z7g = 0;
					z7b = 0;
					break;

		// ZONE 8 //
		case 8:		z8r = 0;
					z8g = 0;
					z8b = 0;
					break;

		// ZONE 9 //
		case 9:		z9r = 0;
					z9g = 0;
					z9b = 0;
					break;

		// ZONE 10 //
		case 10:	z10r = 0;
					z10g = 0;
					z10b = 0;
					break;

		// ZONE 11 //
		case 11:	z11r = 0;
					z11g = 0;
					z11b = 0;
					break;

		// ZONE 12 //
		case 12:	z12r = 0;
					z12g = 0;
					z12b = 0;
					break;
	}	

	// If there are fade cycles left, adjust the current brightness.
	if (stage_fade_steps > 0) {

		// RED LED brightness change towards the target.
		if (zone_brightness_target[current_zone].r != (int)zone_brightness_fade_stepsum[current_zone].r) {
			zone_brightness_fade_stepsum[current_zone].r = zone_brightness_fade_stepsum[current_zone].r + zone_brightness_fade_stepsize[current_zone].r;
			zone_brightness_current[current_zone].r = zone_brightness_fade_stepsum[current_zone].r;
		}
		// GREEN LED brightness change towards the target.
		if (zone_brightness_target[current_zone].g != (int)zone_brightness_fade_stepsum[current_zone].g) {
			zone_brightness_fade_stepsum[current_zone].g = zone_brightness_fade_stepsum[current_zone].g + zone_brightness_fade_stepsize[current_zone].g;
			zone_brightness_current[current_zone].g = zone_brightness_fade_stepsum[current_zone].g;
		}
		// BLUE LED brightness change towards the target.
		if (zone_brightness_target[current_zone].b != (int)zone_brightness_fade_stepsum[current_zone].b) {
			zone_brightness_fade_stepsum[current_zone].b = zone_brightness_fade_stepsum[current_zone].b + zone_brightness_fade_stepsize[current_zone].b;
			zone_brightness_current[current_zone].b = zone_brightness_fade_stepsum[current_zone].b;
		}
	}

	// Reload the zone with the current duty cycle.
	zone_brightness[current_zone] = zone_brightness_current[current_zone];
					
	INTCONbits.GIEL = 1;		// Enable low priority interrupts.

}

void lights_frequency(void)
{
	static unsigned char current_zone = 1;
	static unsigned char i;

	// Cycle through all twelve zones.
	if (current_zone == 12) {
		current_zone = 1;

		// Sync the clocks.
		TMR0H = frequency_high;	
		TMR0L = frequency_low;
	
		TMR1H = dutycycle_high;	
		TMR1L = dutycycle_low;

	} else {
		current_zone++;
	}

	// Turn off the lights in the current zone.
	switch (current_zone) {
		
		// ZONE 1 //
		case 1:		z1r = 0;
					z1g = 0;
					z1b = 0;
					break;

		// ZONE 2 //
		case 2:		z2r = 0;
					z2g = 0;
					z2b = 0;
					break;

		// ZONE 3 //
		case 3:		z3r = 0;
					z3g = 0;
					z3b = 0;
					break;

		// ZONE 4 //
		case 4:		z4r = 0;
					z4g = 0;
					z4b = 0;
					break;

		// ZONE 5 //
		case 5:		z5r = 0;
					z5g = 0;
					z5b = 0;
					break;

		// ZONE 6 //
		case 6:		z6r = 0;
					z6g = 0;
					z6b = 0;
					break;

		// ZONE 7 //
		case 7:		z7r = 0;
					z7g = 0;
					z7b = 0;
					break;

		// ZONE 8 //
		case 8:		z8r = 0;
					z8g = 0;
					z8b = 0;
					break;

		// ZONE 9 //
		case 9:		z9r = 0;
					z9g = 0;
					z9b = 0;
					break;

		// ZONE 10 //
		case 10:	z10r = 0;
					z10g = 0;
					z10b = 0;
					break;

		// ZONE 11 //
		case 11:	z11r = 0;
					z11g = 0;
					z11b = 0;
					break;

		// ZONE 12 //
		case 12:	z12r = 0;
					z12g = 0;
					z12b = 0;
					break;
	}	

	// RED LED brightness change towards the target.
	if (zone_brightness_target[current_zone].r > zone_brightness_current[current_zone].r) {
		zone_brightness_current[current_zone].r++;
	} else if (zone_brightness_target[current_zone].r < zone_brightness_current[current_zone].r) {
		zone_brightness_current[current_zone].r--;
	}

	// GREEN LED brightness change towards the target.
	if (zone_brightness_target[current_zone].g > zone_brightness_current[current_zone].g) {
		zone_brightness_current[current_zone].g++;
	} else if (zone_brightness_target[current_zone].g < zone_brightness_current[current_zone].g) {
		zone_brightness_current[current_zone].g--;
	}

	// BLUE LED brightness change towards the target.
	if (zone_brightness_target[current_zone].b > zone_brightness_current[current_zone].b) {
		zone_brightness_current[current_zone].b++;
	} else if (zone_brightness_target[current_zone].b < zone_brightness_current[current_zone].b) {
		zone_brightness_current[current_zone].b--;
	}
	
	// Reset the current duty cycle.
	zone_brightness[current_zone] = zone_brightness_current[current_zone];

	INTCONbits.GIEL = 1;		// Enable low priority interrupts.

}

void lights_dutycycle(void)
{

	// ZONE 1 //

	// Red //
	if (!z1r) {
		if (zone_brightness[1].r >= 100) {
			z1r = 1;
		} else {
			zone_brightness[1].r++;
		}
	}

	// Green //
	if (!z1g) {
		if (zone_brightness[1].g >= 100) {
			z1g = 1;
		} else {
			zone_brightness[1].g++;
		}
	}

	// Blue //
	if (!z1b) {
		if (zone_brightness[1].b >= 100) {
			z1b = 1;
		} else {
			zone_brightness[1].b++;
		}
	}

	// ZONE 2 //

	// Red //
	if (!z2r) {
		if (zone_brightness[2].r >= 100) {
			z2r = 1;
		} else {
			zone_brightness[2].r++;
		}
	}

	// Green //
	if (!z2g) {
		if (zone_brightness[2].g >= 100) {
			z2g = 1;
		} else {
			zone_brightness[2].g++;
		}
	}

	// Blue //
	if (!z2b) {
		if (zone_brightness[2].b >= 100) {
			z2b = 1;
		} else {
			zone_brightness[2].b++;
		}
	}

	// ZONE 3 //

	// Red //
	if (!z3r) {
		if (zone_brightness[3].r >= 100) {
			z3r = 1;
		} else {
			zone_brightness[3].r++;
		}
	}

	// Green //
	if (!z3g) {
		if (zone_brightness[3].g >= 100) {
			z3g = 1;
		} else {
			zone_brightness[3].g++;
		}
	}

	// Blue //
	if (!z3b) {
		if (zone_brightness[3].b >= 100) {
			z3b = 1;
		} else {
			zone_brightness[3].b++;
		}
	}

	// ZONE 4 //

	// Red //
	if (!z4r) {
		if (zone_brightness[4].r >= 100) {
			z4r = 1;
		} else {
			zone_brightness[4].r++;
		}
	}

	// Green //
	if (!z4g) {
		if (zone_brightness[4].g >= 100) {
			z4g = 1;
		} else {
			zone_brightness[4].g++;
		}
	}

	// Blue //
	if (!z4b) {
		if (zone_brightness[4].b >= 100) {
			z4b = 1;
		} else {
			zone_brightness[4].b++;
		}
	}

	// ZONE 5 //

	// Red //
	if (!z5r) {
		if (zone_brightness[5].r >= 100) {
			z5r = 1;
		} else {
			zone_brightness[5].r++;
		}
	}

	// Green //
	if (!z5g) {
		if (zone_brightness[5].g >= 100) {
			z5g = 1;
		} else {
			zone_brightness[5].g++;
		}
	}

	// Blue //
	if (!z5b) {
		if (zone_brightness[5].b >= 100) {
			z5b = 1;
		} else {
			zone_brightness[5].b++;
		}
	}

	// ZONE 6 //

	// Red //
	if (!z6r) {
		if (zone_brightness[6].r >= 100) {
			z6r = 1;
		} else {
			zone_brightness[6].r++;
		}
	}

	// Green //
	if (!z6g) {
		if (zone_brightness[6].g >= 100) {
			z6g = 1;
		} else {
			zone_brightness[6].g++;
		}
	}

	// Blue //
	if (!z6b) {
		if (zone_brightness[6].b >= 100) {
			z6b = 1;
		} else {
			zone_brightness[6].b++;
		}
	}

	// ZONE 7 //

	// Red //
	if (!z7r) {
		if (zone_brightness[7].r >= 100) {
			z7r = 1;
		} else {
			zone_brightness[7].r++;
		}
	}

	// Green //
	if (!z7g) {
		if (zone_brightness[7].g >= 100) {
			z7g = 1;
		} else {
			zone_brightness[7].g++;
		}
	}

	// Blue //
	if (!z7b) {
		if (zone_brightness[7].b >= 100) {
			z7b = 1;
		} else {
			zone_brightness[7].b++;
		}
	}

	// ZONE 8 //

	// Red //
	if (!z8r) {
		if (zone_brightness[8].r >= 100) {
			z8r = 1;
		} else {
			zone_brightness[8].r++;
		}
	}

	// Green //
	if (!z8g) {
		if (zone_brightness[8].g >= 100) {
			z8g = 1;
		} else {
			zone_brightness[8].g++;
		}
	}

	// Blue //
	if (!z8b) {
		if (zone_brightness[8].b >= 100) {
			z8b = 1;
		} else {
			zone_brightness[8].b++;
		}
	}

	// ZONE 9 //

	// Red //
	if (!z9r) {
		if (zone_brightness[9].r >= 100) {
			z9r = 1;
		} else {
			zone_brightness[9].r++;
		}
	}

	// Green //
	if (!z9g) {
		if (zone_brightness[9].g >= 100) {
			z9g = 1;
		} else {
			zone_brightness[9].g++;
		}
	}

	// Blue //
	if (!z9b) {
		if (zone_brightness[9].b >= 100) {
			z9b = 1;
		} else {
			zone_brightness[9].b++;
		}
	}

	// ZONE 10 //

	// Red //
	if (!z10r) {
		if (zone_brightness[10].r >= 100) {
			z10r = 1;
		} else {
			zone_brightness[10].r++;
		}
	}

	// Green //
	if (!z10g) {
		if (zone_brightness[10].g >= 100) {
			z10g = 1;
		} else {
			zone_brightness[10].g++;
		}
	}

	// Blue //
	if (!z10b) {
		if (zone_brightness[10].b >= 100) {
			z10b = 1;
		} else {
			zone_brightness[10].b++;
		}
	}

	// ZONE 11 //

	// Red //
	if (!z11r) {
		if (zone_brightness[11].r >= 100) {
			z11r = 1;
		} else {
			zone_brightness[11].r++;
		}
	}

	// Green //
	if (!z11g) {
		if (zone_brightness[11].g >= 100) {
			z11g = 1;
		} else {
			zone_brightness[11].g++;
		}
	}

	// Blue //
	if (!z11b) {
		if (zone_brightness[11].b >= 100) {
			z11b = 1;
		} else {
			zone_brightness[11].b++;
		}
	}

	// ZONE 12 //

	// Red //
	if (!z12r) {
		if (zone_brightness[12].r >= 100) {
			z12r = 1;
		} else {
			zone_brightness[12].r++;
		}
	}

	// Green //
	if (!z12g) {
		if (zone_brightness[12].g >= 100) {
			z12g = 1;
		} else {
			zone_brightness[12].g++;
		}
	}

	// Blue //
	if (!z12b) {
		if (zone_brightness[12].b >= 100) {
			z12b = 1;
		} else {
			zone_brightness[12].b++;
		}
	}

	INTCONbits.GIEL = 1;		// Enable low priority interrupts.
}



		