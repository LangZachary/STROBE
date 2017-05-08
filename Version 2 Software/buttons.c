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
		case main_menu1:		switch (*trigger) {
								
									case button_enter_pressed:	oled.menu = select_menu1;
																oled_changed = 1;
																break;
								}break;					
							

		// SELECT MENU //
		case select_menu1:		switch (*trigger) {

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu2;
																oled_changed = 1;
																break;
									
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = main_menu1;
																oled_changed = 1;
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_screen1;
																oled_changed = 1;
																break;
								}break;
							
		
		// SELECT MENU 2 //
		case select_menu2:		switch (*trigger) {

									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu1;
																oled_changed = 1;
																break;
								
									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu3;
																oled_changed = 1;
																break;

									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = main_menu1;
																oled_changed = 1;
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_screen1;
																oled_changed = 1;
																break;
								}break;

		// SELECT MENU 3 //
		case select_menu3:		switch (*trigger) {
	
									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu2;
																oled_changed = 1;
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu4;
																oled_changed = 1;
																break;
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = main_menu1;
																oled_changed = 1;
																break;
								}break;

		// SELECT MENU 4 //
		case select_menu4:		switch (*trigger) {
	
									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu5;
																oled_changed = 1;
																break;
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = main_menu1;
																oled_changed = 1;
																break;
								}break;					
																
		// SELECT MENU 5 //
		case select_menu5:		switch (*trigger) {
	
									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu6;
																oled_changed = 1;
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu4;
																oled_changed = 1;
																break;
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = main_menu1;
																oled_changed = 1;
																break;
								}break;

		// SELECT MENU 6 //
		case select_menu6:		switch (*trigger) {
	
									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu1;
																oled_changed = 1;
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu5;
																oled_changed = 1;
																break;
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = main_menu1;
																oled_changed = 1;
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_screen1;
																oled_changed = 1;
																break;
								}break;

		// MOTION SCREEN 1 //
		case motion_screen1:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = main_menu1;
																oled_changed = 1;
																break;
								}break;

		// MANUAL SCREEN 1 //
		case manual_screen1:	switch (*trigger) {
	
									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_screen2;
																oled_changed = 1;
																break;
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu2;
																oled_changed = 1;
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_new1;
																oled_changed = 1;
																break;
								}break;

		// MANUAL SCREEN 2 //
		case manual_screen2:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu2;
																oled_changed = 1;
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_load1;
																oled_changed = 1;
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_screen1;
																oled_changed = 1;
																break;					
							}break;

		// MANUAL NEW 1 //
		case manual_new1:		switch (menu_state) {

									case 0:			switch (*trigger) {
					
														// MENU PRESSED //
														case button_menu_pressed:	oled.menu = manual_screen1;
																					oled_changed = 1;
																					break;	
					
														// ENTER PRESSED //
														case button_enter_pressed:	oled_menu = manual_new_color;
																					oled_changed = 1;
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
																		oled_changed = 1;								// erase the temporary brightness values.
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
																oled_changed = 1;
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
																oled_changed = 1;
																break;			
								}break;

		// MANUAL LOAD 2 //
		case manual_load2:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_screen2;
																oled_changed = 1;
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
																oled_changed = 1;
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_load3;
																oled_changed = 1;
																break;			
								}break;

		// MANUAL LOAD 3 //
		case manual_load3:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_screen2;
																oled_changed = 1;
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
																oled_changed = 1;
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_load4;
																oled_changed = 1;
																break;		
								}break;

		// MANUAL LOAD 4 //
		case manual_load4:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_screen2;
																oled_changed = 1;
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
																oled_changed = 1;
																break;
			
								}break;
	}	
		
}


