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

	// TEST 
	strobe_lights(led_run);
	// TEST

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

	// Variable for monitoring if a person is holding down a button.
	static unsigned char	button_hold = 0;
	static unsigned char	button_previous = 0;

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
	
		// TEST 
		strobe_lights(led_run);
		// TEST
	
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

		// Test the new button pressed against the previous one.
		if ((button_previous == trigger) && (button_previous != 0)) {

			if (button_hold < 3) {
				button_hold++;
			}

		} else {

			button_hold = 0;

		}

		button_previous = trigger;

		// TEST 
		strobe_lights(led_run);
		// TEST
	
		// Reset all of the debounce variables and the counter to check them five
		// times back to 0.
		button_menu_debounce = 0;
		button_enter_debounce = 0;
		button_up_debounce = 0;
		button_down_debounce = 0;
		button_debounce_counter = 0;
	
		// If there was no button pressed, or the button has been held down for 3 cycles, recheck the buttons in 80ms (4 timer cycle).
		// If there was a button pressed, recheck the buttons in 300ms (15 timer cycles).
		if (button_hold >= 3) {
			button_wait = button_delay_80ms;
		} else if (trigger == 0) {
			button_wait = button_delay_20ms;
		} else {
			button_wait = button_delay_300ms;
		}

	}

	return trigger;
}

/*  Function to act on the pressed button.
 */
void buttons_action(static unsigned char *trigger)
{
	unsigned char i;
	
	// Variable for keeping track of the location being saved to.
	static unsigned char save_location;

	switch (oled.menu){


/**********************************
 *       Motion Sensing           *
 *       Manual                   *
 *       STROBE                   *
 *                     Next       *
 **********************************/	

		// SELECT MENU 1a //
		case select_menu1a:		switch (*trigger) {

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = motion_menu1a_off;
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu1c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;
							
		
		// SELECT MENU 1b //
		case select_menu1b:		switch (*trigger) {

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																break;
								
									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu1c;
																strobe_oled(oled_menu, 0, 0);
																break;


								}break;

		// SELECT MENU 1c //
		case select_menu1c:		switch (*trigger) {

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_menu1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = select_menu1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;
				
/**********************************
 *       Start		              *
 *       Options                  *
 *       Tracking ON              *
 *    Status:        OFF          *
 **********************************/
		// MOTION MENU 1a_off //
		case motion_menu1a_off:	switch (*trigger) {
					
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_motionsensors(ms_deinit);		// Disable Motion Sensing.
																break;	
					
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1a_on;
																strobe_oled(oled_menu, 0, 0);		// Show ON on the display.
																strobe_motionsensors(ms_init);		// Initialize motion sensing.
																strobe_lights(led_ms_init);			// Initialize lights.				
																break;
				
									// UP PRESSED //
									case button_up_pressed:		if (ms_tracking) {
																	oled.menu = motion_menu1c_on;
																} else {
																	oled.menu = motion_menu1c_off;
																}							
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = motion_menu1b;
																strobe_oled(oled_menu, 0, 0);						
																break;
								}break;

		// MOTION MENU 1a_on //
		case motion_menu1a_on:	switch (*trigger) {
					
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_motionsensors(ms_deinit);		// Disable motion sensing.
																break;	
					
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1a_off;
																strobe_oled(oled_menu, 0, 0);		// Show OFF on the display.
																strobe_motionsensors(ms_deinit);		// Deinitialize motion sensing.	
																strobe_lights(led_deinit);			// Deinitialize lights.			
																break;
				
									// UP PRESSED //
									case button_up_pressed:		if (ms_tracking) {
																	oled.menu = motion_menu1c_on;
																} else {
																	oled.menu = motion_menu1c_off;
																}							
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = motion_menu1b;
																strobe_oled(oled_menu, 0, 0);						
																break;
								}break;

		// MOTION MENU 1b //
		case motion_menu1b:		switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_motionsensors(ms_deinit);		// Disable motion sensing.
																break;	
					
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu2a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_init);							// Enable ADC Start Sequence.
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
																strobe_oled(oled_menu, 0, 0);
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	if (ms_tracking) {
																	oled.menu = motion_menu1c_on;
																} else {
																	oled.menu = motion_menu1c_off;
																}							
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

		// MOTION MENU 1c_off //
		case motion_menu1c_off:	switch (*trigger) {
					
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_motionsensors(ms_deinit);		// Disable motion sensing.
																break;	
					
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1c_on;
																strobe_oled(oled_menu, 0, 0);		// Show ON on the display.
																ms_tracking = 1;			
																break;
									// UP PRESSED //
									case button_up_pressed:		oled.menu = motion_menu1b;						
																strobe_oled(oled_menu, 0, 0);
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	if (ms_timer) {
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}							
																strobe_oled(oled_menu, 0, 0);
																break;	
								}break;

		// MOTION MENU 1c_on //
		case motion_menu1c_on:	switch (*trigger) {
					
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_motionsensors(ms_deinit);		// Disable motion sensing.
																break;	
					
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1c_off;
																strobe_oled(oled_menu, 0, 0);		// Show ON on the display.
																ms_tracking = 0;			
																break;
									// UP PRESSED //
									case button_up_pressed:		oled.menu = motion_menu1b;						
																strobe_oled(oled_menu, 0, 0);
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	if (ms_timer) {
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}							
																strobe_oled(oled_menu, 0, 0);
																break;	
								}break;


/**********************************
 *   Timeout Delay:   xxx         *
 *       |             |          *
 *       Light Spread             *
 *       |             |          *
 **********************************/

		// MOTION MENU 2a //
		case motion_menu2a:		switch (*trigger) {

									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = motion_menu1;							// Reprint the motion sensor menu.
																strobe_oled(oled_menu, 0, 0);

																if (ms_timer) {										// Reprint whether the motion sensor is ON/OFF.
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}
																strobe_oled(oled_menu, 0, 0);

																if (ms_tracking) {									// Reprint whether the tracking is ON/OFF.
																	oled.menu = motion_menu1c_on;
																} else {
																	oled.menu = motion_menu1c_off;
																}
																strobe_oled(oled_menu, 0, 0);

																oled.menu = motion_menu1b;							// Point back to options.
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_deinit);						// Enable ADC Stop Sequence.
																zone_timeout_delay = zone_timeout_delay_old;		// Revert to the old value.
																adjacent_brightness = adjacent_brightness_old;		// Revert to the old values.
																adjacent2_brightness = adjacent2_brightness_old;	// Revert to the old values.
																adjacent3_brightness = adjacent3_brightness_old;	// Revert to the old values.				
																break;
	
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = motion_menu1;							// Reprint the motion sensor menu.
																strobe_oled(oled_menu, 0, 0);

																if (ms_timer) {										// Reprint whether the motion sensor is ON/OFF.
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}
																strobe_oled(oled_menu, 0, 0);

																if (ms_tracking) {									// Reprint whether the tracking is ON/OFF.
																	oled.menu = motion_menu1c_on;
																} else {
																	oled.menu = motion_menu1c_off;
																}
																strobe_oled(oled_menu, 0, 0);

																oled.menu = motion_menu1b;							// Point back to options.
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_deinit);						// Enable ADC Stop Sequence.			
																break;
								}break;


/**********************************
 *     		  Manual              *
 *     New						  *
 *     Load						  *
 *     							  *
 **********************************/

		// MANUAL MENU 1a //
		case manual_menu1a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = select_menu1b;				// Point at Manual.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu2;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_manual_init);			// Initialize lights.
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_menu1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL MENU 1b //
		case manual_menu1b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = select_menu1b;				// Point at Manual.
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu3;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_menu1a;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;



/**********************************
 *     Zone          All          *
 *     Red   |                 |  *
 *     Green |                 |  *
 *     Blue  |                 |  *
 **********************************/

		// MANUAL MENU 2a //
		case manual_menu2a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_save1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu2a_zone;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);
																zone_select_old = zone_select; 			// Save the current zone.
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu2d;
																strobe_oled(oled_menu, 0, 0);						
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_menu2b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL MENU 2a - Zone //
		case manual_menu2a_zone:switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																oled.menu = manual_menu2a;
																strobe_oled(oled_menu, 0, 0);
																zone_select = zone_select_old; 			// Reload the old zone.
																strobe_oled(oled_zone, 0, 0);			// Display the old zone.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																oled.menu = manual_menu2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		if (zone_select == 12) {
																	zone_select = 0;
																	print_progress_bar(1, 9, 0);
																	print_progress_bar(2, 9, 0);
																	print_progress_bar(3, 9, 0);
																} else {
																	zone_select++;
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].r);
																	print_progress_bar(2, 9, zone_brightness_target[zone_select].g);
																	print_progress_bar(3, 9, zone_brightness_target[zone_select].b);
																}
																strobe_oled(oled_zone, 0, 0);							
																break;			

									// DOWN PRESSED //
									case button_down_pressed:	if (zone_select == 0) {
																	zone_select = 12;
																} else {
																	zone_select--;
																}

																if (zone_select == 0) {
																	print_progress_bar(1, 9, 0);
																	print_progress_bar(2, 9, 0);
																	print_progress_bar(3, 9, 0);
																} else {
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].r);
																	print_progress_bar(2, 9, zone_brightness_target[zone_select].g);
																	print_progress_bar(3, 9, zone_brightness_target[zone_select].b);
																}
																strobe_oled(oled_zone, 0, 0);	
																break;
								}break;

		// MANUAL MENU 2b //
		case manual_menu2b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_save1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu2b_red;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);				// Initialize Blinking of "Red".
																strobe_adc(adc_single_init);			// Enable ADC Start Sequence.
																
																// Save the current brightness
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target_old[i].r = zone_brightness_target[i].r;
																	}
																} else {
																	zone_brightness_target_old[zone_select].r = zone_brightness_target[zone_select].r;
																}
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu2a;
																strobe_oled(oled_menu, 0, 0);						
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_menu2c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL MENU 2b - Red //
		case manual_menu2b_red:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);			// Enable ADC Stop Sequence.
																oled.menu = manual_menu2b;
																strobe_oled(oled_menu, 0, 0);

																// Revert to the old brightness.
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target[i].r = zone_brightness_target_old[i].r;
																	}
																	print_progress_bar(1, 9, zone_brightness_target_old[1].r);
																} else {
																	zone_brightness_target[zone_select].r = zone_brightness_target_old[zone_select].r;
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].r);
																}

																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);			// Enable ADC Stop Sequence.
																oled.menu = manual_menu2b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL MENU 2c //
		case manual_menu2c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_save1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu2c_green;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);				// Initialize Blinking of "Red".
																strobe_adc(adc_single_init);			// Enable ADC Start Sequence.
																
																// Save the current brightness
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target_old[i].g = zone_brightness_target[i].g;
																	}
																} else {
																	zone_brightness_target_old[zone_select].g = zone_brightness_target[zone_select].g;
																}
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu2b;
																strobe_oled(oled_menu, 0, 0);						
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_menu2d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL MENU 2c - Green //
		case manual_menu2c_green:switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);				// Enable ADC Stop Sequence.
																oled.menu = manual_menu2c;
																strobe_oled(oled_menu, 0, 0);

																// Revert to the old brightness.
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target[i].g = zone_brightness_target_old[i].g;
																	}
																	print_progress_bar(1, 9, zone_brightness_target_old[1].g);
																} else {
																	zone_brightness_target[zone_select].g = zone_brightness_target_old[zone_select].g;
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].g);
																}

																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);			// Enable ADC Stop Sequence.
																oled.menu = manual_menu2c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL MENU 2d //
		case manual_menu2d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_save1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu2d_blue;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);				// Initialize Blinking of "Red".
																strobe_adc(adc_single_init);			// Enable ADC Start Sequence.
																
																// Save the current brightness
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target_old[i].b = zone_brightness_target[i].b;
																	}
																} else {
																	zone_brightness_target_old[zone_select].b = zone_brightness_target[zone_select].b;
																}
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu2c;
																strobe_oled(oled_menu, 0, 0);						
																break;	
									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_menu2a;
																strobe_oled(oled_menu, 0, 0);
																break;


								}break;

		// MANUAL MENU 2d - Blue //
		case manual_menu2d_blue:switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);				// Enable ADC Stop Sequence.
																oled.menu = manual_menu2c;
																strobe_oled(oled_menu, 0, 0);

																// Revert to the old brightness.
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target[i].b = zone_brightness_target_old[i].b;
																	}
																	print_progress_bar(1, 9, zone_brightness_target_old[1].b);
																} else {
																	zone_brightness_target[zone_select].b = zone_brightness_target_old[zone_select].b;
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].b);
																}

																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);			// Enable ADC Stop Sequence.
																oled.menu = manual_menu2d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

/**********************************
 *    1. Empty                    *
 * 	  2. Empty       			  *
 *	  3. Empty               	  *
 *    4. Empty    				  *
 **********************************/

		// MANUAL MENU 3a //
		case manual_menu3a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_menu1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = manual_menu1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu2;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_manual_init);				// Initialize lights.
																mem_manual_load_lights(1);
																// Insert code to read EEPROM //	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu3d;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_menu3b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL MENU 3b //
		case manual_menu3b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_menu1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = manual_menu1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu2;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_manual_init);				// Initialize lights.
																mem_manual_load_lights(2);
																// Insert code to read EEPROM //	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu3a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_menu3c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL MENU 3c //
		case manual_menu3c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_menu1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = manual_menu1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu2;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_manual_init);				// Initialize lights.
																mem_manual_load_lights(3);
																// Insert code to read EEPROM //	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu3b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_menu3d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL MENU 3d //
		case manual_menu3d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_menu1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = manual_menu1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu2;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_manual_init);				// Initialize lights.
																mem_manual_load_lights(4);
																// Insert code to read EEPROM //	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_menu3c;
																strobe_oled(oled_menu, 0, 0);
																break;
									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_menu3a;
																strobe_oled(oled_menu, 0, 0);
																break;


								}break;


/**********************************
 *     	Do you wish to            *
 * 		    Save?     			  *
 *			 Yes             	  *
 *     	     No   				  *
 **********************************/

		// MANUAL SAVE 1a //
		case manual_save1a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_menu2;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_save2;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_save1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_save1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL SAVE 1b //
		case manual_save1b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_menu2;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_menu1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																strobe_lights(led_deinit);				// Disable lights.		
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_save1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_save1a;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

/**********************************
 *    1. Empty                    *
 * 	  2. Empty       			  *
 *	  3. Empty               	  *
 *    4. Empty    				  *
 **********************************/

		// MANUAL SAVE 2a //
		case manual_save2a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_menu2a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_save_name1;
																strobe_mem(mem_save_init, 1, trigger);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_save2d;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_save2b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL SAVE 2b //
		case manual_save2b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_menu2a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_save_name2;
																strobe_mem(mem_save_init, 2, trigger);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_save2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_save2c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL SAVE 2c //
		case manual_save2c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_menu2a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_save_name3;
																strobe_mem(mem_save_init, 3, trigger);	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_save2b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_save2d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL SAVE 2d //
		case manual_save2d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = manual_menu2a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = manual_save_name4;
																strobe_mem(mem_save_init, 4, trigger);	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = manual_save2c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = manual_save2a;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// MANUAL SAVE NAME //
		case manual_save_name1:	strobe_mem(mem_save_run, 1, trigger);
								break;
		case manual_save_name2: strobe_mem(mem_save_run, 2, trigger);
								break;
		case manual_save_name3: strobe_mem(mem_save_run, 3, trigger);
								break;
		case manual_save_name4:	strobe_mem(mem_save_run, 4, trigger);
								break;

/**********************************
 *     		  STROBE              *
 *     Short Show				  *
 *     Long Show				  *
 *     Strobe Light				  *
 **********************************/

		// STROBE MENU 1a //
		case strobe_menu1a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = select_menu1c;					// Point back at STROBE
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_menu1c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_menu1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE MENU 1b //
		case strobe_menu1b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = select_menu1c;					// Point back at STROBE
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_menu1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_menu1c;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

		// STROBE MENU 1c //
		case strobe_menu1c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = select_menu1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = select_menu1c;					// Point back at STROBE
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_strobe1a;
																strobe_oled(oled_menu, 0, 0);
																lights_strobelight();
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_menu1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_menu1a;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

/**********************************
 *     STROBE Short Show          *
 *     New 						  *
 *     Load						  *
 *     							  *
 **********************************/

		// STROBE SHORT 1a //
		case strobe_short1a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_menu1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_new1;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT 1b //
		case strobe_short1b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_menu1a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_load1;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

/**********************************
 *    1. Empty                    *
 * 	  2. Empty       			  *
 *	  3. Empty               	  *
 *    4. Empty    				  *
 **********************************/

		// STROBE SHORT NEW 1a //
		case strobe_short_new1a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 1;
																lights_stage(stage_save_init, stage_save_slot);	
																oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new1d;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 1b //
		case strobe_short_new1b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 2;
																lights_stage(stage_save_init, stage_save_slot);	
																oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new1c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 1c //
		case strobe_short_new1c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 3;
																lights_stage(stage_save_init, stage_save_slot);	
																oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new1d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 1d //
		case strobe_short_new1d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 4;
																lights_stage(stage_save_init, stage_save_slot);	
																oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new1c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new1a;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

/**********************************
 *    Stage         /32           *
 * 	  Change Colors   			  *
 *	  Change Timing           	  *
 *    Next      Back       Done   *
 **********************************/

		// STROBE SHORT NEW 2a //
		case strobe_short_new2a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_new3;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new3a;
																strobe_oled(oled_menu, 0, 0);
																strobe_oled(oled_zone, 0, 0);	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new2e;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new2b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 2b //
		case strobe_short_new2b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short_exit1a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_new4;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_init);							// Enable ADC Start Sequence.
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new2c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 2c //
		case strobe_short_new2c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	lights_stage(stage_save_run, 0);
																oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new2b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new2d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 2d //
		case strobe_short_new2d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	lights_stage(stage_save_run, 0);
																oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2d;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new2c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new2e;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

		// STROBE SHORT NEW 2e //
		case strobe_short_new2e:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	lights_stage(stage_save_run, 0);
																oled.menu = strobe_short_save_name;
																strobe_oled(oled_menu, 0, 0);
																strobe_mem(mem_save_init, stage_save_slot, trigger);		
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new2d;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

/**********************************
 *     Zone          All          *
 *     Red   |                 |  *
 *     Green |                 |  *
 *     Blue  |                 |  *
 **********************************/

		// STROBE SHORT NEW 3a //
		case strobe_short_new3a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_new3a_zone;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);
																zone_select_old = zone_select; // Save the current zone.
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new3d;
																strobe_oled(oled_menu, 0, 0);						
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new3b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 3a - Zone //
		case strobe_short_new3a_zone:switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																oled.menu = strobe_short_new3a;
																strobe_oled(oled_menu, 0, 0);
																zone_select = zone_select_old; // Reload the old zone.
																strobe_oled(oled_zone, 0, 0);		 // Display the old zone.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																oled.menu = strobe_short_new3a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		if (zone_select == 12) {
																	zone_select = 0;
																} else {
																	zone_select++;
																}
																strobe_oled(oled_zone, 0, 0);							
																break;			

									// DOWN PRESSED //
									case button_down_pressed:	if (zone_select == 0) {
																	zone_select = 12;
																} else {
																	zone_select--;
																}
																strobe_oled(oled_zone, 0, 0);	
																break;
								}break;

		// STROBE SHORT NEW 3b //
		case strobe_short_new3b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_new3b_red;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);				// Initialize Blinking of "Red".
																strobe_adc(adc_single_init);			// Enable ADC Start Sequence.
																
																// Save the current brightness
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target_old[i].r = zone_brightness_target[i].r;
																	}
																} else {
																	zone_brightness_target_old[zone_select].r = zone_brightness_target[zone_select].r;
																}
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new3a;
																strobe_oled(oled_menu, 0, 0);						
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new3c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 3b - Red //
		case strobe_short_new3b_red:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);				// Enable ADC Stop Sequence.
																oled.menu = strobe_short_new3b;
																strobe_oled(oled_menu, 0, 0);

																// Revert to the old brightness.
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target[i].r = zone_brightness_target_old[i].r;
																	}
																	print_progress_bar(1, 9, zone_brightness_target_old[1].r);
																} else {
																	zone_brightness_target[zone_select].r = zone_brightness_target_old[zone_select].r;
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].r);
																}

																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);			// Enable ADC Stop Sequence.
																oled.menu = strobe_short_new3b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 3c //
		case strobe_short_new3c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_new3c_green;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);				// Initialize Blinking of "Red".
																strobe_adc(adc_single_init);			// Enable ADC Start Sequence.
																
																// Save the current brightness
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target_old[i].g = zone_brightness_target[i].g;
																	}
																} else {
																	zone_brightness_target_old[zone_select].g = zone_brightness_target[zone_select].g;
																}
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new3b;
																strobe_oled(oled_menu, 0, 0);						
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new3d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 3c - Green //
		case strobe_short_new3c_green:switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);				// Enable ADC Stop Sequence.
																oled.menu = strobe_short_new3c;
																strobe_oled(oled_menu, 0, 0);

																// Revert to the old brightness.
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target[i].g = zone_brightness_target_old[i].g;
																	}
																	print_progress_bar(1, 9, zone_brightness_target_old[1].g);
																} else {
																	zone_brightness_target[zone_select].g = zone_brightness_target_old[zone_select].g;
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].g);
																}

																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);			// Enable ADC Stop Sequence.
																oled.menu = strobe_short_new3c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT NEW 3d //
		case strobe_short_new3d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_new3d_blue;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);				// Initialize Blinking of "Red".
																strobe_adc(adc_single_init);			// Enable ADC Start Sequence.
																
																// Save the current brightness
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target_old[i].b = zone_brightness_target[i].b;
																	}
																} else {
																	zone_brightness_target_old[zone_select].b = zone_brightness_target[zone_select].b;
																}
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_new3c;
																strobe_oled(oled_menu, 0, 0);						
																break;	
									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_new3a;
																strobe_oled(oled_menu, 0, 0);
																break;


								}break;

		// STROBE SHORT NEW 3d - Blue //
		case strobe_short_new3d_blue:switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);				// Enable ADC Stop Sequence.
																oled.menu = strobe_short_new3c;
																strobe_oled(oled_menu, 0, 0);

																// Revert to the old brightness.
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target[i].b = zone_brightness_target_old[i].b;
																	}
																	print_progress_bar(1, 9, zone_brightness_target_old[1].b);
																} else {
																	zone_brightness_target[zone_select].b = zone_brightness_target_old[zone_select].b;
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].b);
																}

																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);			// Enable ADC Stop Sequence.
																oled.menu = strobe_short_new3d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;



/**********************************
 *   Hold Time:           2s      *
 *       |             |          *
 *   Fade In Time:        2s      *
 *       |             |          *
 **********************************/

		// STROBE SHORT NEW 4 //
		case strobe_short_new4:	switch (*trigger) {

									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2b;					// Go back to Change Timing
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_deinit);							// Enable ADC Stop Sequence.
/*																if (ms_timer) {										// Reprint whether the motion sensor is ON/OFF.
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}
																strobe_oled(oled_menu, 0, 0);

																if (ms_tracking) {									// Reprint whether the tracking is ON/OFF.
																	oled.menu = motion_menu1c_on;
																} else {
																	oled.menu = motion_menu1c_off;
																}
																strobe_oled(oled_menu, 0, 0);

																oled.menu = motion_menu1b;							// Point back to options.
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_deinit);							// Enable ADC Stop Sequence.
																zone_timeout_delay = zone_timeout_delay_old;		// Revert to the old value.
																adjacent_brightness = adjacent_brightness_old;		// Revert to the old values.
																adjacent2_brightness = adjacent2_brightness_old;	// Revert to the old values.
																adjacent3_brightness = adjacent3_brightness_old;	// Revert to the old values.				
*/																break;
	
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2b;					// Go back to Change Timing
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_deinit);							// Enable ADC Stop Sequence.
/*																if (ms_timer) {										// Reprint whether the motion sensor is ON/OFF.
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}
																strobe_oled(oled_menu, 0, 0);

																if (ms_tracking) {									// Reprint whether the tracking is ON/OFF.
																	oled.menu = motion_menu1c_on;
																} else {
																	oled.menu = motion_menu1c_off;
																}
																strobe_oled(oled_menu, 0, 0);

																oled.menu = motion_menu1b;							// Point back to options.
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_deinit);							// Enable ADC Stop Sequence.			
*/																break;
								}break;

		// STROBE SAVE NAME //
		case strobe_short_save_name:	strobe_mem(mem_save_run, stage_save_slot, trigger);
										break;

/**********************************
 *    Exit without saving?        *
 * 	                     		  *
 *	           Yes            	  *
 *              No                *
 **********************************/

		// STROBE EXIT //
		// Cursor >> No			
		case strobe_short_exit1a:	switch (*trigger) {
	
									// ENTER PRESSED //
									case button_enter_pressed:	// Go back to short save menu.
																oled.menu = strobe_short_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_exit1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_exit1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// Cursor >> Yes		
		case strobe_short_exit1b:	switch (*trigger) {
	
									// ENTER PRESSED //
									case button_enter_pressed:	// Go back to Strobe main menu.
																oled.menu = strobe_menu1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_deinit); 
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;
		// Cursor >> No
		case strobe_long_exit1a:switch (*trigger) {
	
									// ENTER PRESSED //
									case button_enter_pressed:	// Go back to long save menu.
																oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_exit1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_exit1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;	

		// Cursor >> Yes		
		case strobe_long_exit1b:	switch (*trigger) {
	
									// ENTER PRESSED //
									case button_enter_pressed:	// Go back to Strobe main menu.
																oled.menu = strobe_menu1a;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_deinit); 
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;




/**********************************
 *    1. Empty                    *
 * 	  2. Empty       			  *
 *	  3. Empty               	  *
 *    4. Empty    				  *
 **********************************/

		// STROBE SHORT LOAD 1a //
		case strobe_short_load1a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 1;	
																oled.menu = strobe_short_load2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_load2a_off;
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_load1d;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_load1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT LOAD 1b //
		case strobe_short_load1b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 2;	
																oled.menu = strobe_short_load2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_load2a_off;
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_load1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_load1c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT LOAD 1c //
		case strobe_short_load1c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 3;	
																oled.menu = strobe_short_load2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_load2a_off;
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_load1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_load1d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE SHORT LOAD 1d //
		case strobe_short_load1d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 4;	
																oled.menu = strobe_short_load2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short_load2a_off;
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_load1c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_load1a;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

/**********************************
 *   		 Show Loaded:         *
 * 	  				  			  *
 *	  Start		               	  *
 *    Edit		   				  *
 **********************************/

		// STROBE SHORT LOAD 2a OFF //
		case strobe_short_load2a_off:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_load2a_on;
																strobe_oled(oled_menu, 0, 0);
																lights_stage(stage_init, 0);	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_load1c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_load2b;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

		// STROBE SHORT LOAD 2a ON //
		case strobe_short_load2a_on:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short1b;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_deinit);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_short_load2a_off;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_deinit);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_short_load2b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_short_load2b;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

		// STROBE SHORT LOAD 2b //
		case strobe_short_load2b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_short1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_short1b;
																strobe_oled(oled_menu, 0, 0);

																if (oled.buffer[2][5] == 'o') {
																	strobe_lights(led_deinit);
																}
																break;

									// ENTER PRESSED //
							//		case button_enter_pressed:	oled.menu = strobe_short_load3;
							//									strobe_oled(oled_menu, 0, 0);
															//	lights_stage(stage_init, 4);
															//	strobe_lights(led_stage_init);	
																break;

									// UP PRESSED //
									case button_up_pressed:		if (oled.buffer[2][5] == 'o') {
																	oled.menu = strobe_short_load2a_on;
																} else {
																	oled.menu = strobe_short_load2a_off;
																}
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWNB PRESSED //
									case button_down_pressed:	if (oled.buffer[2][5] == 'o') {
																	oled.menu = strobe_short_load2a_on;
																} else {
																	oled.menu = strobe_short_load2a_off;
																}
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;


/**********************************
 *     STROBE Long Show          *
 *     New 						  *
 *     Load						  *
 *     							  *
 **********************************/

		// STROBE LONG 1a //
		case strobe_long1a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_menu1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_new1;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG 1b //
		case strobe_long1b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_menu1a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_load1;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

/**********************************
 *    1. Empty                    *
 * 	  2. Empty       			  *
 *	  3. Empty               	  *
 *    4. Empty    				  *
 **********************************/

		// STROBE LONG NEW 1a //
		case strobe_long_new1a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 5;
																lights_stage(stage_save_init, stage_save_slot);	
																oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new1d;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 1b //
		case strobe_long_new1b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 6;
																lights_stage(stage_save_init, stage_save_slot);	
																oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new1c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 1c //
		case strobe_long_new1c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 7;
																lights_stage(stage_save_init, stage_save_slot);	
																oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new1d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 1d //
		case strobe_long_new1d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 8;
																lights_stage(stage_save_init, stage_save_slot);	
																oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new1c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new1a;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;



/**********************************
 *    Stage         /192          *
 * 	  Change Colors   			  *
 *	  Change Timing           	  *
 *    Next      Back       Done   *
 **********************************/

		// STROBE LONG NEW 2a //
		case strobe_long_new2a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_new3;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new3a;
																strobe_oled(oled_menu, 0, 0);
																strobe_oled(oled_zone, 0, 0);	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new2e;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new2b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 2b //
		case strobe_long_new2b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long_exit1a;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_new4;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_init);							// Enable ADC Start Sequence.
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new2c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 2c //
		case strobe_long_new2c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	lights_stage(stage_save_run, 0);
																oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new2b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new2d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 2d //
		case strobe_long_new2d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	lights_stage(stage_save_run, 0);
																oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2d;
																strobe_oled(oled_menu, 0, 0);	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new2c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new2e;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

		// STROBE LONG NEW 2e //
		case strobe_long_new2e:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long_exit1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	lights_stage(stage_save_run, 0);
																oled.menu = strobe_long_save_name;
																strobe_oled(oled_menu, 0, 0);
																strobe_mem(mem_save_init, stage_save_slot - 4, trigger);		
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new2d;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

/**********************************
 *     Zone          All          *
 *     Red   |                 |  *
 *     Green |                 |  *
 *     Blue  |                 |  *
 **********************************/

		// STROBE LONG NEW 3a //
		case strobe_long_new3a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_new3a_zone;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);
																zone_select_old = zone_select; // Save the current zone.
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new3d;
																strobe_oled(oled_menu, 0, 0);						
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new3b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 3a - Zone //
		case strobe_long_new3a_zone:switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																oled.menu = strobe_long_new3a;
																strobe_oled(oled_menu, 0, 0);
																zone_select = zone_select_old; // Reload the old zone.
																strobe_oled(oled_zone, 0, 0);		 // Display the old zone.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																oled.menu = strobe_long_new3a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// UP PRESSED //
									case button_up_pressed:		if (zone_select == 12) {
																	zone_select = 0;
																} else {
																	zone_select++;
																}
																strobe_oled(oled_zone, 0, 0);							
																break;			

									// DOWN PRESSED //
									case button_down_pressed:	if (zone_select == 0) {
																	zone_select = 12;
																} else {
																	zone_select--;
																}

																strobe_oled(oled_zone, 0, 0);	
																break;
								}break;

		// STROBE LONG NEW 3b //
		case strobe_long_new3b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_new3b_red;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);				// Initialize Blinking of "Red".
																strobe_adc(adc_single_init);			// Enable ADC Start Sequence.
																
																// Save the current brightness
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target_old[i].r = zone_brightness_target[i].r;
																	}
																} else {
																	zone_brightness_target_old[zone_select].r = zone_brightness_target[zone_select].r;
																}
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new3a;
																strobe_oled(oled_menu, 0, 0);						
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new3c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 3b - Red //
		case strobe_long_new3b_red:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);				// Enable ADC Stop Sequence.
																oled.menu = strobe_long_new3b;
																strobe_oled(oled_menu, 0, 0);

																// Revert to the old brightness.
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target[i].r = zone_brightness_target_old[i].r;
																	}
																	print_progress_bar(1, 9, zone_brightness_target_old[1].r);
																} else {
																	zone_brightness_target[zone_select].r = zone_brightness_target_old[zone_select].r;
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].r);
																}

																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);			// Enable ADC Stop Sequence.
																oled.menu = strobe_long_new3b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 3c //
		case strobe_long_new3c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_new3c_green;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);				// Initialize Blinking of "Red".
																strobe_adc(adc_single_init);			// Enable ADC Start Sequence.
																
																// Save the current brightness
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target_old[i].g = zone_brightness_target[i].g;
																	}
																} else {
																	zone_brightness_target_old[zone_select].g = zone_brightness_target[zone_select].g;
																}
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new3b;
																strobe_oled(oled_menu, 0, 0);						
																break;	

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new3d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 3c - Green //
		case strobe_long_new3c_green:switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);				// Enable ADC Stop Sequence.
																oled.menu = strobe_long_new3c;
																strobe_oled(oled_menu, 0, 0);

																// Revert to the old brightness.
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target[i].g = zone_brightness_target_old[i].g;
																	}
																	print_progress_bar(1, 9, zone_brightness_target_old[1].g);
																} else {
																	zone_brightness_target[zone_select].g = zone_brightness_target_old[zone_select].g;
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].g);
																}

																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);			// Enable ADC Stop Sequence.
																oled.menu = strobe_long_new3c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG NEW 3d //
		case strobe_long_new3d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2a;
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_single_deinit);			// Disable ADC.
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_new3d_blue;
																strobe_oled(oled_menu, 0, 0);
																strobe_blink(blink_init);				// Initialize Blinking of "Red".
																strobe_adc(adc_single_init);			// Enable ADC Start Sequence.
																
																// Save the current brightness
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target_old[i].b = zone_brightness_target[i].b;
																	}
																} else {
																	zone_brightness_target_old[zone_select].b = zone_brightness_target[zone_select].b;
																}
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_new3c;
																strobe_oled(oled_menu, 0, 0);						
																break;	
									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_new3a;
																strobe_oled(oled_menu, 0, 0);
																break;


								}break;

		// STROBE LONG NEW 3d - Blue //
		case strobe_long_new3d_blue:switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);				// Enable ADC Stop Sequence.
																oled.menu = strobe_long_new3c;
																strobe_oled(oled_menu, 0, 0);

																// Revert to the old brightness.
																if (zone_select == 0) {
																	for (i = 1; i <=12; i++) {
																		zone_brightness_target[i].b = zone_brightness_target_old[i].b;
																	}
																	print_progress_bar(1, 9, zone_brightness_target_old[1].b);
																} else {
																	zone_brightness_target[zone_select].b = zone_brightness_target_old[zone_select].b;
																	print_progress_bar(1, 9, zone_brightness_target[zone_select].b);
																}

																break;

									// ENTER PRESSED //
									case button_enter_pressed:	strobe_blink(blink_deinit);
																strobe_adc(adc_single_deinit);			// Enable ADC Stop Sequence.
																oled.menu = strobe_long_new3d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;



/**********************************
 *   Hold Time:           2s      *
 *       |             |          *
 *   Fade In Time:        2s      *
 *       |             |          *
 **********************************/

		// STROBE LONG NEW 4 //
		case strobe_long_new4:	switch (*trigger) {

									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2b;					// Go back to Change Timing
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_deinit);							// Enable ADC Stop Sequence.
/*																if (ms_timer) {										// Reprint whether the motion sensor is ON/OFF.
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}
																strobe_oled(oled_menu, 0, 0);

																if (ms_tracking) {									// Reprint whether the tracking is ON/OFF.
																	oled.menu = motion_menu1c_on;
																} else {
																	oled.menu = motion_menu1c_off;
																}
																strobe_oled(oled_menu, 0, 0);

																oled.menu = motion_menu1b;							// Point back to options.
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_deinit);						// Enable ADC Stop Sequence.
																zone_timeout_delay = zone_timeout_delay_old;		// Revert to the old value.
																adjacent_brightness = adjacent_brightness_old;		// Revert to the old values.
																adjacent2_brightness = adjacent2_brightness_old;	// Revert to the old values.
																adjacent3_brightness = adjacent3_brightness_old;	// Revert to the old values.				
*/																break;
	
									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_new2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_new2b;					// Go back to Change Timing
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_deinit);							// Enable ADC Stop Sequence.
/*																if (ms_timer) {										// Reprint whether the motion sensor is ON/OFF.
																	oled.menu = motion_menu1a_on;
																} else {
																	oled.menu = motion_menu1a_off;
																}
																strobe_oled(oled_menu, 0, 0);

																if (ms_tracking) {									// Reprint whether the tracking is ON/OFF.
																	oled.menu = motion_menu1c_on;
																} else {
																	oled.menu = motion_menu1c_off;
																}
																strobe_oled(oled_menu, 0, 0);

																oled.menu = motion_menu1b;							// Point back to options.
																strobe_oled(oled_menu, 0, 0);
																strobe_adc(adc_dual_deinit);							// Enable ADC Stop Sequence.			
*/																break;
								}break;

		// STROBE SAVE NAME //
		case strobe_long_save_name:	strobe_mem(mem_save_run, stage_save_slot, trigger);
										break;


/**********************************
 *    1. Empty                    *
 * 	  2. Empty       			  *
 *	  3. Empty               	  *
 *    4. Empty    				  *
 **********************************/

		// STROBE LONG LOAD 1a //
		case strobe_long_load1a:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 5;	
																oled.menu = strobe_long_load2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_load2a_off;
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_load1d;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_load1b;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG LOAD 1b //
		case strobe_long_load1b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 6;	
																oled.menu = strobe_long_load2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_load2a_off;
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_load1a;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_load1c;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG LOAD 1c //
		case strobe_long_load1c:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 7;	
																oled.menu = strobe_long_load2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_load2a_off;
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_load1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_load1d;
																strobe_oled(oled_menu, 0, 0);
																break;
								}break;

		// STROBE LONG LOAD 1d //
		case strobe_long_load1d:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long1b;					// Point back at Load.
																strobe_oled(oled_menu, 0, 0);	
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	stage_save_slot = 8;	
																oled.menu = strobe_long_load2;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long_load2a_off;
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_load1c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_load1a;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

/**********************************
 *   		 Show Loaded:         *
 * 	  				  			  *
 *	  Start		               	  *
 *    Edit		   				  *
 **********************************/

		// STROBE LONG LOAD 2a OFF //
		case strobe_long_load2a_off:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long1b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_load2a_on;
																strobe_oled(oled_menu, 0, 0);
																lights_stage(stage_init, 0);	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_load1c;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_load2b;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

		// STROBE LONG LOAD 2a ON //
		case strobe_long_load2a_on:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long1b;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_deinit);
																break;

									// ENTER PRESSED //
									case button_enter_pressed:	oled.menu = strobe_long_load2a_off;
																strobe_oled(oled_menu, 0, 0);
																strobe_lights(led_deinit);
														//		lights_stage(stage_deinit, 0);	
																break;

									// UP PRESSED //
									case button_up_pressed:		oled.menu = strobe_long_load2b;
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWN PRESSED //
									case button_down_pressed:	oled.menu = strobe_long_load2b;
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;

		// STROBE LONG LOAD 2b //
		case strobe_long_load2b:	switch (*trigger) {
	
									// MENU PRESSED //
									case button_menu_pressed:	oled.menu = strobe_long1a;
																strobe_oled(oled_menu, 0, 0);
																oled.menu = strobe_long1b;
																strobe_oled(oled_menu, 0, 0);

																if (oled.buffer[2][5] == 'o') {
																	lights_stage(stage_init, 4);
																}
																break;

									// ENTER PRESSED //
							//		case button_enter_pressed:	oled.menu = strobe_long_load3;
							//									strobe_oled(oled_menu, 0, 0);
															//	lights_stage(stage_init, 4);
															//	strobe_lights(led_stage_init);	
																break;

									// UP PRESSED //
									case button_up_pressed:		if (oled.buffer[2][5] == 'o') {
																	oled.menu = strobe_long_load2a_on;
																} else {
																	oled.menu = strobe_long_load2a_off;
																}
																strobe_oled(oled_menu, 0, 0);
																break;

									// DOWNB PRESSED //
									case button_down_pressed:	if (oled.buffer[2][5] == 'o') {
																	oled.menu = strobe_long_load2a_on;
																} else {
																	oled.menu = strobe_long_load2a_off;
																}
																strobe_oled(oled_menu, 0, 0);
																break;

								}break;
	}	
		
}


