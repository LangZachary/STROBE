
/*****************************************************************************************
 *                                     Blink											 *
 *****************************************************************************************/

/*  Root function for processing blinking menu items.
 */
void strobe_blink(unsigned char blink_process)
{
	static unsigned char blink_enable = 0;

	// Variable passed into the function decides which process is completed.
	// 1 - Initialize the blinking function on the current menu item.
	// 2 - Disable blinking.
	// 3 - General operation.
	switch (blink_process) {

		// Initialization Process //
		case blink_init: {		

					strobe_lights(led_run);			// Check the lights.

					
					blink_ready = 0;				// Set up the timer for setting delay
					blink_timer_flag = 0;			// between blinks.
					blink_count = blink_delay_on;	// ON delay.
					blink_timer = 1;				// Turn on the blink timer.
					blink_enable = 1;				// Turn on blink control in the general blink process.
		
				} break;

		// Deinitialization Process //
		case blink_deinit: {

					blink(1);						// Turn on the menu item immediately.
					blink_timer = 0;				// Turn off the blink timer.
					blink_enable = 0;				// Disable blinking.

				} break;

		// General Operation //
		case blink_run: {

					if (!blink_enable) {
						break;
					}
		
					if (!blink_ready) {
						break;
					}

					strobe_lights(led_run);			// Check the lights.

					blink(0);
			
				} break;
	}
}

// General Blinking Operation.
// Based on the current menu active, this function will blink a menu item ON/OFF.
// The item will be on for 600ms and off for 300ms.
// If a 1 is passed into the function the menu item is immediately turned on.
void blink(unsigned char force_on)
{

	static unsigned char blink_on = 1;

	switch (oled.menu) {

		// Manual Menu Items //

		// Zone
		case strobe_short_new3a_zone:
		case strobe_long_new3a_zone:
		case manual_menu2a_zone: {

									strobe_lights(led_run);				// Check the lights.

									if (force_on) {							// Blinking has been disabled.
										oled.buffer[0][3] = 'Z';		// Turn the menu item on immediately.
										oled.buffer[0][4] = 'o';
										oled.buffer[0][5] = 'n';
										oled.buffer[0][6] = 'e';
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										break;
									}

									if (blink_on) {						// The menu item is currently on.
										oled.buffer[0][3] = ' ';		// Turn the item off.
										oled.buffer[0][4] = ' ';
										oled.buffer[0][5] = ' ';
										oled.buffer[0][6] = ' ';
										blink_on = 0;					// Signal that the menu item is off.
										blink_count = blink_delay_off;	// Start off delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.

									} else {							// The menu item is currently off.		
										oled.buffer[0][3] = 'Z';		// Turn the item on.
										oled.buffer[0][4] = 'o';
										oled.buffer[0][5] = 'n';
										oled.buffer[0][6] = 'e';
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.
									}
								} break;

		// Red
		case strobe_short_new3b_red:
		case strobe_long_new3b_red:
		case manual_menu2b_red: {

									strobe_lights(led_run);				// Check the lights.

									if (force_on) {						// Blinking has been disabled.
										oled.buffer[1][3] = 'R';		// Turn the menu item on immediately.
										oled.buffer[1][4] = 'e';
										oled.buffer[1][5] = 'd';
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										break;
									}

									if (blink_on) {						// The menu item is currently on.
										oled.buffer[1][3] = ' ';		// Turn the item off.
										oled.buffer[1][4] = ' ';
										oled.buffer[1][5] = ' ';
										blink_on = 0;					// Signal that the menu item is off.
										blink_count = blink_delay_off;	// Start off delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.

									} else {							// The menu item is currently off.		
										oled.buffer[1][3] = 'R';		// Turn the item on.
										oled.buffer[1][4] = 'e';
										oled.buffer[1][5] = 'd';
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.
									}
								} break;

		// Green
		case strobe_short_new3c_green:
		case strobe_long_new3c_green:
		case manual_menu2c_green: {

									strobe_lights(led_run);				// Check the lights.		// TEST

									if (force_on) {						// Blinking has been disabled.
										oled.buffer[2][3] = 'G';		// Turn the menu item on immediately.
										oled.buffer[2][4] = 'r';
										oled.buffer[2][5] = 'e';
										oled.buffer[2][6] = 'e';
										oled.buffer[2][7] = 'n';
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										break;
									}

									if (blink_on) {						// The menu item is currently on.
										oled.buffer[2][3] = ' ';		// Turn the item off.
										oled.buffer[2][4] = ' ';
										oled.buffer[2][5] = ' ';
										oled.buffer[2][6] = ' ';
										oled.buffer[2][7] = ' ';
										blink_on = 0;					// Signal that the menu item is off.
										blink_count = blink_delay_off;	// Start off delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.

									} else {							// The menu item is currently off.		
										oled.buffer[2][3] = 'G';		// Turn the item on.
										oled.buffer[2][4] = 'r';
										oled.buffer[2][5] = 'e';
										oled.buffer[2][6] = 'e';
										oled.buffer[2][7] = 'n';
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.
									}
								} break;

		// Blue
		case strobe_short_new3d_blue:
		case strobe_long_new3d_blue:
		case manual_menu2d_blue: {

									strobe_lights(led_run);				// Check the lights.

									if (force_on) {						// Blinking has been disabled.
										oled.buffer[3][3] = 'B';		// Turn the menu item on immediately.
										oled.buffer[3][4] = 'l';
										oled.buffer[3][5] = 'u';
										oled.buffer[3][6] = 'e';
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										break;
									}

									if (blink_on) {						// The menu item is currently on.
										oled.buffer[3][3] = ' ';		// Turn the item off.
										oled.buffer[3][4] = ' ';
										oled.buffer[3][5] = ' ';
										oled.buffer[3][6] = ' ';
										blink_on = 0;					// Signal that the menu item is off.
										blink_count = blink_delay_off;	// Start off delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.

									} else {							// The menu item is currently off.		
										oled.buffer[3][3] = 'B';		// Turn the item on.
										oled.buffer[3][4] = 'l';
										oled.buffer[3][5] = 'u';
										oled.buffer[3][6] = 'e';
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.
									}
								} break;

		case strobe_long_save_name: {
									if (force_on) {						// Blinking has been disabled.
										oled.buffer[stage_save_slot - 5][current_letter + 5] = name[current_letter]; // Force the current item to reappear.
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										break;
									}

									if (blink_on) {						// The menu item is currently on.
										oled.buffer[stage_save_slot - 5][current_letter + 5] = ' ';		// Turn the item off.
										blink_on = 0;					// Signal that the menu item is off.
										blink_count = blink_delay_off;	// Start off delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.

									} else {							// The menu item is currently off.		
										oled.buffer[stage_save_slot - 5][current_letter + 5] = name[current_letter];
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.
									}
								} break;

		case strobe_short_save_name: {
									if (force_on) {						// Blinking has been disabled.
										oled.buffer[stage_save_slot - 1][current_letter + 5] = name[current_letter]; // Force the current item to reappear.
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										break;
									}

									if (blink_on) {						// The menu item is currently on.
										oled.buffer[stage_save_slot - 1][current_letter + 5] = ' ';		// Turn the item off.
										blink_on = 0;					// Signal that the menu item is off.
										blink_count = blink_delay_off;	// Start off delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.

									} else {							// The menu item is currently off.		
										oled.buffer[stage_save_slot - 1][current_letter + 5] = name[current_letter];
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.
									}
								} break;

		case manual_save_name1: {

									strobe_lights(led_run);				// Check the lights.

									if (force_on) {						// Blinking has been disabled.
										oled.buffer[0][current_letter + 5] = name[current_letter]; // Force the current item to reappear.
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										break;
									}

									if (blink_on) {						// The menu item is currently on.
										oled.buffer[0][current_letter + 5] = ' ';		// Turn the item off.
										blink_on = 0;					// Signal that the menu item is off.
										blink_count = blink_delay_off;	// Start off delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.

									} else {							// The menu item is currently off.		
										oled.buffer[0][current_letter + 5] = name[current_letter];
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.
									}
								} break;

		case manual_save_name2: {

									strobe_lights(led_run);				// Check the lights.

									if (force_on) {						// Blinking has been disabled.
										oled.buffer[1][current_letter + 5] = name[current_letter]; // Force the current item to reappear.
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										break;
									}

									if (blink_on) {						// The menu item is currently on.
										oled.buffer[1][current_letter + 5] = ' ';		// Turn the item off.
										blink_on = 0;					// Signal that the menu item is off.
										blink_count = blink_delay_off;	// Start off delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.

									} else {							// The menu item is currently off.		
										oled.buffer[1][current_letter + 5] = name[current_letter];
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.
									}
								} break;

		case manual_save_name3: {

									strobe_lights(led_run);				// Check the lights.

									if (force_on) {						// Blinking has been disabled.
										oled.buffer[2][current_letter + 5] = name[current_letter]; // Force the current item to reappear.
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										break;
									}

									if (blink_on) {						// The menu item is currently on.
										oled.buffer[2][current_letter + 5] = ' ';		// Turn the item off.
										blink_on = 0;					// Signal that the menu item is off.
										blink_count = blink_delay_off;	// Start off delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.

									} else {							// The menu item is currently off.		
										oled.buffer[2][current_letter + 5] = name[current_letter];
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.
									}
								} break;

		case manual_save_name4: {

									strobe_lights(led_run);				// Check the lights.

									if (force_on) {						// Blinking has been disabled.
										oled.buffer[3][current_letter + 5] = name[current_letter]; // Force the current item to reappear.
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										break;
									}

									if (blink_on) {						// The menu item is currently on.
										oled.buffer[3][current_letter + 5] = ' ';		// Turn the item off.
										blink_on = 0;					// Signal that the menu item is off.
										blink_count = blink_delay_off;	// Start off delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.

									} else {							// The menu item is currently off.		
										oled.buffer[3][current_letter + 5] = name[current_letter];
										blink_on = 1;					// Signal that the menu item is on.
										blink_count = blink_delay_on;	// Start on delay.
										blink_ready = 0;				// Reset flag to wait for the next blink.
									}
								} break;

		default:				break;
	}
		
}

