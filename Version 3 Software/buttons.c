/*****************************************************************************************
 *                                    BUTTONS											 *
 *****************************************************************************************/

/*  Root function for processing buttons.
 *  button_wait is a variable that gets decremented every 20ms. It is set to 1 when
 *  the buttons have been checked but none pressed, and set to 25 when a button is
 *  pressed.  This is so there is a .5s delay between button presses. When it hits 0,
 *  the buttons are ready to be read / processed.
 *  If a button is pressed an action is taken and the buttons pressed is reset.
 */
void strobe_buttons(void)
{
	// Variable for checking which button was pressed.
	static unsigned char	button_pressed = 0;

	// Check if new buttons can be processed yet.
	if (button_wait > 0) {
		return;
	}

	// Read the buttons.
	button_pressed = buttons_check();


	// If there is a button pressed act upon it and then reset.
	if (button_pressed > 0) {
		buttons_action(&button_pressed);
		button_pressed = 0;
	}
}

/*  Function to check the buttons.
 *  The buttons are checked 5 times every 100ms. The times they are active is tallied
 *  and at the end of 100ms if a button has been active more than 2 times it is considered
 *  pressed.  When multiple buttons are pressed the priority is MENU > ENTER > UP > DOWN.
 *  When a button is pressed *trigger is set to that button constant.
 *  button_wait is reset to 1 if no button has been pressed and 25 if a button has been
 *  pressed so the buttons are not checked again for 20ms and 500ms accordingly.
 */
unsigned char buttons_check(void)
{

	unsigned char trigger = 0;

	// Variable for checking how many times the buttons have been checked in one cycle.
	// The buttons are checked every 20ms up to five times.
	static unsigned char	button_debounce_counter = 0;

	// Variables for tallying buttons times high.
	static unsigned char	button_up_debounce = 0;
	static unsigned char	button_down_debounce = 0;
	static unsigned char	button_enter_debounce = 0;
	static unsigned char	button_menu_debounce = 0;

	// If the buttons have not been checked 5 times then check them again. If a button
	// is high, add 1 to the corresponding debounce variable.
	if (button_debounce_counter < 5) {
		
		if (!button_up) {
			button_up_debounce++;
		}

		if (!button_down) {
			button_down_debounce++;
		}

		if (!button_enter) {
			button_enter_debounce++;
		}
	
		if (!button_menu) {
			button_menu_debounce++;
		}
		
		// Increment the counter saying the buttons were checked again.
		button_debounce_counter++;

	// If the buttons have been checked 5 times, return the value of the one checked.
	// There is priority given to MENU >> ENTER >> UP >> DOWN.
	} else {

		if (button_menu_debounce > 2) {
			trigger = button_menu_pressed;

		} else if (button_enter_debounce > 2) {
			trigger = button_enter_pressed;

		} else if (button_up_debounce > 2) {
			trigger = button_up_pressed;

		} else if (button_down_debounce > 2) {
			trigger = button_down_pressed;
		}
	
	// Reset all of the debounce variables and the counter to check them five
	// times back to 0.
	button_menu_debounce = 0;
	button_enter_debounce = 0;
	button_up_debounce = 0;
	button_down_debounce = 0;
	button_debounce_counter = 0;

	}

	// If there was no button pressed, recheck the buttons in 20ms (1 timer cycle).
	// If there was a button pressed, recheck the buttons in 500ms (25 timer cycles).
	if (trigger == 0) {
		button_wait = 1;
	} else {
		button_wait = 25;
	}

	return trigger;
}

/*  Function to act on the pressed button.
 */
void buttons_action(static unsigned char *trigger)
{
	unsigned char i;
	
	// Variable for keeping track of the current menu state to allow for specific changes
	// to be made when necessary.
	static unsigned char menu_state = 0;

	switch (oled.menu){

		// MAIN MENU //
		case welcome_screen1:	switch (*trigger) {

									// ENTER PRESSED //								
									case button_enter_pressed:	oled.menu = select_menu1a;
																strobe_oled(load_menu, 0, 0);
																break;
								}break;					
							

		// SELECT MENU 1a //
		case select_menu1a:		switch (*trigger) {
									
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = welcome_screen1;
																strobe_oled(load_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1a_off;
																strobe_oled(load_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu1b;
																strobe_oled(load_menu, 0, 0);
																break;
								}break;
							
		
		// SELECT MENU 1b //
		case select_menu1b:		switch (*trigger) {

									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = welcome_screen1;
																strobe_oled(load_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu1a;
																strobe_oled(load_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu1a;
																strobe_oled(load_menu, 0, 0);
																break;
								
									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu1c;
																strobe_oled(load_menu, 0, 0);
																break;


								}break;

		// SELECT MENU 1c //
		case select_menu1c:		switch (*trigger) {

									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = welcome_screen1;
																strobe_oled(load_menu, 0, 0);
																break;	

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_menu1a;
																strobe_oled(load_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu1b;
																strobe_oled(load_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu1d;
																strobe_oled(load_menu, 0, 0);
																break;
								}break;

		// SELECT MENU 1d //
		case select_menu1d:		switch (*trigger) {

									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = welcome_screen1;
																strobe_oled(load_menu, 0, 0);

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = select_menu2a;
																strobe_oled(load_menu, 0, 0);
																break;																break;
	
									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu1c;
																strobe_oled(load_menu, 0, 0);
																break;
	

								}break;					
																
		// SELECT MENU 2a //
		case select_menu2a:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(load_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu2b;
																strobe_oled(load_menu, 0, 0);
																break;
	

								}break;

		// SELECT MENU 2b //
		case select_menu2b:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(load_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = select_menu1a;
																strobe_oled(load_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu2a;
																strobe_oled(load_menu, 0, 0);
																break;
								}break;

		// MOTION MENU 1a_off //
		case motion_menu1a_off:	switch (*trigger) {
					
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(load_menu, 0, 0);
																strobe_motionsensors(deinitialize);		// Disable motion sensing.
																break;	
					
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1a_on;
																strobe_oled(load_menu, 0, 0);			// Show ON on the display.
																strobe_motionsensors(initialize);		// Initialize motion sensing.
																strobe_lights(initialize);				// Initialize lights.				
																break;
				
									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = motion_menu1b;
																strobe_oled(load_menu, 0, 0);						
																break;
								}break;

		// MOTION MENU 1a_on //
		case motion_menu1a_on:	switch (*trigger) {
					
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(load_menu, 0, 0);
																strobe_motionsensors(deinitialize);		// Disable motion sensing.
																break;	
					
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1a_off;
																strobe_oled(load_menu, 0, 0);			// Show OFF on the display.
																strobe_motionsensors(deinitialize);		// Initialize motion sensing.				
																break;
				
									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = motion_menu1b;
																strobe_oled(load_menu, 0, 0);						
																break;
								}break;

		// MOTION MENU 1b //
		case motion_menu1b:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(load_menu, 0, 0);
																strobe_motionsensors(deinitialize);		// Disable motion sensing.
																break;	
					
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu2a;
																strobe_oled(load_menu, 0, 0);
																strobe_adc(initialize);								// Enable ADC Start Sequence.
																zone_timeout_delay_old = zone_timeout_delay;		// Store the old value
																adjacent_brightness_old = adjacent_brightness;		// Store the old values.
																adjacent2_brightness_old = adjacent2_brightness;	// Store the old values.
																adjacent3_brightness_old = adjacent3_brightness;	// Store the old values.																
																break;
				
									// UP PRESSED //
									case button_up_pressed:		if (ms_timer) {
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}							
																strobe_oled(load_menu, 0, 0);
																break;	

								}break;

		// MOTION MENU 2a //
		case motion_menu2a:		switch (*trigger) {

									// MENU PRESSED //
									case button_menu_pressed:	if (ms_timer) {
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}
																strobe_oled(load_menu, 0, 0);
																strobe_adc(deinitialize);							// Enable ADC Stop Sequence.
																zone_timeout_delay = zone_timeout_delay_old;		// Revert to the old value.
																adjacent_brightness = adjacent_brightness_old;		// Revert to the old values.
																adjacent2_brightness = adjacent2_brightness_old;	// Revert to the old values.
																adjacent3_brightness = adjacent3_brightness_old;	// Revert to the old values.				
																break;
	
									// ENTER PRESSED //
									case button_enter_pressed:	if (ms_timer) {
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}
																strobe_oled(load_menu, 0, 0);	
																strobe_adc(deinitialize);							// Enable ADC Stop Sequence.			
																break;
								}break;
/*
		// MOTION MENU 2b //
		case motion_menu2b:		switch (*trigger) {
	
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1a;
																strobe_oled(load_menu, 0, 0);
																adc_enable = 0;					// Disable ADC Control.
																adc_timer = 0;					// Disable ADC Timer.
																zone_timeout_delay = zone_timeout_delay_old;	// Revert to the old value.					
																break;	

									// UP PRESSED //
									case button_up_pressed:		oled.menu = motion_menu2a;
																strobe_oled(load_menu, 0, 0);
																break;				
								}break;

		// MOTION MENU 3a //
		case motion_menu3a:		switch (*trigger) {
	
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1a;
																strobe_oled(load_menu, 0, 0);	
																adc_enable = 0;					// Disable ADC Control.
																adc_timer = 0;					// Disable ADC Timer.				
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = motion_menu3b;
																strobe_oled(load_menu, 0, 0);						
																break;				
								}break;

		// MOTION MENU 3b //
		case motion_menu3b:		switch (*trigger) {
	
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1a;
																strobe_oled(load_menu, 0, 0);
																adc_enable = 0;					// Disable ADC Control.
																adc_timer = 0;					// Disable ADC Timer.
																adjacent_brightness = adjacent_brightness_old;	// Revert to the old values.
																adjacent2_brightness = adjacent2_brightness_old;
																adjacent3_brightness = adjacent3_brightness_old;						
																break;	

									// UP PRESSED //
									case button_up_pressed:		oled.menu = motion_menu3a;
																strobe_oled(load_menu, 0, 0);
																break;				
								}break;

		// MANUAL SCREEN 1 //
		case manual_menu1a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(load_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_new1;
																strobe_oled(load_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_screen2;
																strobe_oled(load_menu, 0, 0);
																break;
								}break;

		// MANUAL SCREEN 2 //
		case manual_screen2:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(load_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_load1;
																strobe_oled(load_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu1a;
																strobe_oled(load_menu, 0, 0);
																break;					
							}break;

		// MANUAL NEW 1 //
		case manual_new1:		switch (menu_state) {

									case 0:			switch (*trigger) {
					
														// MENU PRESSED //
														case button_menu_pressed:	oled.menu = manual_menu1a;
																					strobe_oled(load_menu, 0, 0);
																					break;	
					
														// ENTER PRESSED //
														case button_enter_pressed:	oled_menu = manual_new_color;
																					strobe_oled(load_menu, 0, 0);
																					adc_enable = 1;						
																					break;
				
														// DOWN PRESSED //
														case button_down_pressed:	if (oled.display[1][1] == '>') {	// If the cursor is pointing at "Change Color"
																						oled.buffer[1][1] = ' ';		// Move the cursor down to
																						oled.buffer[2][1] = '>';		// "Change Delay".
																						oled_buffer = 1;				// Flag new info in the buffer.
																					}		
																					if (oled.display[1][1] == '>') {	// If the cursor is pointing at "Change Delay"
																						oled.buffer[1][1] = ' ';		// Move the cursor down to
																						oled.buffer[2][1] = '>';		// "Change Delay".
																						oled_buffer = 1;				// Flag new info in the buffer.
																					}									
																					break;
						
												}break;
								}						

		// MANUAL NEW COLOR //
		case manual_new_color:		switch (*trigger) {
	
										// MENU PRESSED //
										case button_menu_pressed:	if (manual_change_red) {							// If currently changing one of the colors,
																		manual_change_red = 0;							// simply exit that corresponding mode and don't change the display.
																	} else if (manual_change_green) {
																		manual_change_green = 0;
																	} else if (manual_change_blue) {
																		manual_change_blue = 0;	
																	} else {						
																		oled.menu = manual_new1;						// If not currently changing a color, leave the adjust color menu and
																		strobe_oled(load_menu, 0, 0);								// erase the temporary brightness values.
																		manual_brightness_red_temp = manual_brightness_red;
																		manual_brightness_green_temp = manual_brightness_green;
																		manual_brightness_blue_temp = manual_brightness_blue;
																	}break;
	
										// ENTER PRESSED //
										case button_enter_pressed:					
																	break;
	
										// UP PRESSED //
										case button_up_pressed:		if (oled.display[1][1] == '>') {	// If the cursor is pointing at "Green"
																		oled.buffer[1][1] = ' ';		// Move the cursor down to
																		oled.buffer[0][1] = '>';		// "Red".
																		oled_buffer = 1;				// Flag new info in the buffer.
																	}		
																	if (oled.display[2][1] == '>') {	// If the cursor is pointing at "Blue"
																		oled.buffer[2][1] = ' ';		// Move the cursor down to
																		oled.buffer[1][1] = '>';		// "Green".
																		oled_buffer = 1;				// Flag new info in the buffer.
																	}	
																	if (oled.display[3][1] == '>') {	// If the cursor is pointing at "Save"
																		oled.buffer[3][1] = ' ';		// Move the cursor down to
																		oled.buffer[2][1] = '>';		// "Blue".
																		oled_buffer = 1;				// Flag new info in the buffer.
																	}															
																	break;	

										// DOWN PRESSED //
										case button_down_pressed:	if (oled.display[0][1] == '>') {	// If the cursor is pointing at "Red"
																		oled.buffer[0][1] = ' ';		// Move the cursor down to
																		oled.buffer[1][1] = '>';		// "Green".
																		oled_buffer = 1;				// Flag new info in the buffer.
																	}		
																	if (oled.display[1][1] == '>') {	// If the cursor is pointing at "Green"
																		oled.buffer[1][1] = ' ';		// Move the cursor down to
																		oled.buffer[2][1] = '>';		// "Blue".
																		oled_buffer = 1;				// Flag new info in the buffer.
																	}	
																	if (oled.display[2][1] == '>') {	// If the cursor is pointing at "Blue"
																		oled.buffer[2][1] = ' ';		// Move the cursor down to
																		oled.buffer[3][1] = '>';		// "Save".
																		oled_buffer = 1;				// Flag new info in the buffer.
																	}															
																	break;		
									}break;

		// MANUAL LOAD 1 //
		case manual_load1:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_screen2;
																strobe_oled(load_menu, 0, 0);
																for (i = 1; i <= 6; i++) {
																	zone_brightness_target[i].r = 0;
																	zone_brightness_target[i].g = 0;
																	zone_brightness_target[i].b = 0;
																}
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	for (i = 1; i <= 6; i++) {
																	zone_brightness_target[i].r = 0;
																	zone_brightness_target[i].g = 0;
																	zone_brightness_target[i].b = 100;
																}							
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_load2;
																strobe_oled(load_menu, 0, 0);
																break;			
								}break;

		// MANUAL LOAD 2 //
		case manual_load2:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_screen2;
																strobe_oled(load_menu, 0, 0);
																for (i = 1; i <= 6; i++) {
																	zone_brightness_target[i].r = 0;
																	zone_brightness_target[i].g = 0;
																	zone_brightness_target[i].b = 0;
																}
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	for (i = 1; i <= 6; i++) {
																	zone_brightness_target[i].r = 0;
																	zone_brightness_target[i].g = 100;
																	zone_brightness_target[i].b = 0;
																}							
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_load1;
																strobe_oled(load_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_load3;
																strobe_oled(load_menu, 0, 0);
																break;			
								}break;

		// MANUAL LOAD 3 //
		case manual_load3:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_screen2;
																strobe_oled(load_menu, 0, 0);
																for (i = 1; i <= 6; i++) {
																	zone_brightness_target[i].r = 0;
																	zone_brightness_target[i].g = 0;
																	zone_brightness_target[i].b = 0;
																}
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	for (i = 1; i <= 6; i++) {
																	zone_brightness_target[i].r = 100;
																	zone_brightness_target[i].g = 0;
																	zone_brightness_target[i].b = 0;
																}							
																break;	

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_load2;
																strobe_oled(load_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_load4;
																strobe_oled(load_menu, 0, 0);
																break;		
								}break;

		// MANUAL LOAD 4 //
		case manual_load4:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_screen2;
																strobe_oled(load_menu, 0, 0);
																for (i = 1; i <= 6; i++) {
																	zone_brightness_target[i].r = 0;
																	zone_brightness_target[i].g = 0;
																	zone_brightness_target[i].b = 0;
																}
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	for (i = 1; i <= 6; i++) {
																	zone_brightness_target[i].r = 100;
																	zone_brightness_target[i].g = 20;
																	zone_brightness_target[i].b = 0;
																}							
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_load3;
																strobe_oled(load_menu, 0, 0);
																break;
			
								}break;
*/
	}	
		
}


