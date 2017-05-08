
/*****************************************************************************************
 *                                      OLED											 *
 *****************************************************************************************/

/*  Root function for processing OLED.
 *  First oled_changed is checked to see if the buffer needs different data (menu changed).
 *  Second oled_buffer is checked to see if the buffer has new data that needs to put to the
 *  display and if the display is ready for a new command it is done.
 */
void strobe_oled(unsigned char oled_process, unsigned char dial1, unsigned char dial2)
{
	static unsigned char new_data = 0;

	// Variable passed into the function decides which process is completed.
	// 1 - Load the oled buffer with new menu data.
	// 2 - Load the oled buffer with new adc data.
	// 3 - General operation.
	switch (oled_process) {

		// Load buffer with new menu data.
		case 1: {

					oled_load_menu();			
			
				} break;

		// Load buffer with new adc data.
		case 2: {

					oled_load_adc(dial1, dial2);

				} break;

		// Send buffer data to the OLED.
		case 3: {

					// If OLED is not read for more data END.
					if (!oled_ready) {
						break;
					}
						
					// Send new data to the OLED.
					oled_send_buffer();

				} break;
	}
}

/*  Sends data in the OLED buffer to the menu.
 *  This function reads the location in the OLED buffer (oled.buffer) pointed to
 *  by the line variable (oled.line) and position variable (oled.position) and sees
 *  if it matches the data already on the OLED (oled.display).  If the data is new,
 *  the byte is sent to the OLED, the position is increased by 1 (position + 1, if
 *  at the end of the line position = 1 and next line), and the new data is saved
 *  to oled.display.  If the data is not new, the function goes to the next position
 *  until it finds a location that has new data.  When the function finishes checking/
 *  changing the last position, it will clear the oled.buffer bit to say that all
 *  the buffer data has been transferred.
 */
void oled_send_buffer(void)
{

	static unsigned char	new_location = 0;

	// Main OLED Loop.	
	while (1) {

	// If the pointer is in the last position of any line, go to the next line and return. This allows the
	// longest action to be checking one line of data and finding no new data.
	if (oled.position == 20) {
		
		switch (oled.line) {
			
			case 0: { // >>> Line 1.
					oled.line = 1;
				} break;

			case 1: { // >>> Line 2.
					oled.line = 2;
				} break;

			case 2: { // >>> Line 3.
					oled.line = 3;
				} break;
			
			case 3: { // >>> Line 0.
					oled.line = 0;
				} break;
			
			// Error.
			default: { // >>> Line 0.
					oled.line = 0;
				} break;
		}
		
		oled.position = 0;		// >>> Position 0.
		
		oled_move_cursor();		// Move the cursor.
		
		return;
	}

	// See if there is new data in the current location to be printed.
	// Print the new data to the display, change oled.display to show it has the new data.
	if (oled.display[oled.line][oled.position] != oled.buffer[oled.line][oled.position]) {

		// If locations have been skipped, move the cursor to the current position.
		if (new_location) {

			oled_move_cursor();		// Move the cursor to the current location.
			new_location = 0;
			
			return;
		}
		
		// Print the new data to the OLED to the proper location.	
		oled_print(oled.buffer[oled.line][oled.position]);

		// Save the data printed to the oled.display array to keep track of the displayed data.
		oled.display[oled.line][oled.position] = oled.buffer[oled.line][oled.position];

		// Increment the position of the cursor.
		oled.position = oled.position + 1;

		return;
	}

	// Increment the position of the cursor.
	oled.position++;	

	// Indicate the cursor needs to be moved if new data is found.
	new_location = 1;

	}
}


/*  Processes a change to the OLED menu.
 *  This function reads the 10 bit char oled_menu and decides what is supposed to be displayed
 *  on the OLED display.  The function then loads the oled buffer with the new menu to be sent
 *  to the display in the array: oled.buffer[4][20].
 *  A 1 is returned from the function when it is completed.
 */
void oled_load_menu(void)
{

	switch (oled.menu) {

		// Welcome Screen
		case welcome_screen1:  	strcpypgm2ram(oled.buffer[0], welcome_screen1_l1);	// Set the screen to the welcome screen
			 	 				strcpypgm2ram(oled.buffer[1], welcome_screen1_l2);	// with the name of the device, version
  				 				strcpypgm2ram(oled.buffer[2], welcome_screen1_l3);	// number and writer.
  				 				strcpypgm2ram(oled.buffer[3], welcome_screen1_l4);
				 				break;

		// Select Menu 1
		// Cursor > Motion Sensing
		case select_menu1a:		strcpypgm2ram(oled.buffer[0], select_menu1_l1);		// Set the screen to Select Menu 1
			 	 				strcpypgm2ram(oled.buffer[1], select_menu1_l2);		// Motion Sensing, Manual, STROBE, Next.
  				 				strcpypgm2ram(oled.buffer[2], select_menu1_l3);
  				 				strcpypgm2ram(oled.buffer[3], select_menu1_l4);
								oled.buffer[0][2] = oled_cursor;					// Point the cursor at Motion Sensing.
								break;

		// Cursor > Manual
		case select_menu1b:		oled.buffer[1][2] = oled_cursor;					// Point the cursor at Manual.
								oled.buffer[0][2] = oled_space;
								oled.buffer[2][2] = oled_space;
								break;

		// Cursor > STROBE
		case select_menu1c:		oled.buffer[2][2] = oled_cursor;					// Point the cursor at SROBE.
								oled.buffer[1][2] = oled_space;
								oled.buffer[3][12] = oled_space;
								break;

		// Cursor > Next
		case select_menu1d:		oled.buffer[3][12] = oled_cursor;					// Point the cursor at Next.					
								oled.buffer[2][2] = oled_space;
								break;

		// Select Menu 2
		// Cursor > Options
		case select_menu2a:		strcpypgm2ram(oled.buffer[0], select_menu2_l1);		// Set the screen to Select Menu 2
			 	 				strcpypgm2ram(oled.buffer[1], select_menu2_l2);		// Options, Next.
 	 				 			strcpypgm2ram(oled.buffer[2], select_menu2_l3);
  					 			strcpypgm2ram(oled.buffer[3], select_menu2_l4);
								oled.buffer[0][2] = oled_cursor;					// Point the cursor at Options.
								break;

		// Cursor > Next
		case select_menu2b:		oled.buffer[3][12] = oled_cursor;					// Point the cursor at Motion Sensing.
								oled.buffer[0][2] = oled_space;
								break;

		// Motion Menu 1
		// Cursor > Start
		// Off
		case motion_menu1a_off:	strcpypgm2ram(oled.buffer[0], motion_menu1a_off_l1);
				 	 			strcpypgm2ram(oled.buffer[1], motion_menu1a_off_l2);
	  				 			strcpypgm2ram(oled.buffer[2], motion_menu1a_off_l3);
	  				 			strcpypgm2ram(oled.buffer[3], motion_menu1a_off_l4);
								oled.buffer[0][2] = oled_cursor;					// Point the cursor at Start.
								break;

		// Cursor > Stop
		// On
		case motion_menu1a_on:	strcpypgm2ram(oled.buffer[0], motion_menu1a_on_l1);
				 	 			strcpypgm2ram(oled.buffer[1], motion_menu1a_on_l2);
	  				 			strcpypgm2ram(oled.buffer[2], motion_menu1a_on_l3);
	  				 			strcpypgm2ram(oled.buffer[3], motion_menu1a_on_l4);				
								oled.buffer[0][2] = oled_cursor;					// Point the cursor at Stop.
								break;

		// Cursor > Options
		case motion_menu1b:		oled.buffer[1][2] = oled_cursor;					// Point the cursor at Timeout Delay.
								oled.buffer[0][2] = oled_space;
								oled.buffer[2][2] = oled_space;
								break;

		// Motion Menu 2
		case motion_menu2a:		strcpypgm2ram(oled.buffer[0], motion_menu2_l1);
				 	 			strcpypgm2ram(oled.buffer[1], motion_menu2_l2);
	  				 			strcpypgm2ram(oled.buffer[2], motion_menu2_l3);
	  				 			strcpypgm2ram(oled.buffer[3], motion_menu2_l4);	
								break;

		// Motion Menu 3
		// Cursor > Save
		case motion_menu3a:		strcpypgm2ram(oled.buffer[0], motion_menu3_l1);
				 	 			strcpypgm2ram(oled.buffer[1], motion_menu3_l2);
	  				 			strcpypgm2ram(oled.buffer[2], motion_menu3_l3);
	  				 			strcpypgm2ram(oled.buffer[3], motion_menu3_l4);	
								oled.buffer[2][2] = oled_cursor;					// Point the cursor at Save.
								oled.buffer[3][2] = oled_space;
								break;

		// Cursor > Cancel
		case motion_menu3b:		oled.buffer[3][2] = oled_cursor;					// Point the cursor at Cancel.
								oled.buffer[2][2] = oled_space;
								break;

		case manual_menu1a:		strcpypgm2ram(oled.buffer[0], manual_menu1_l1);
			 	 				strcpypgm2ram(oled.buffer[1], manual_menu1_l2);
  				 				strcpypgm2ram(oled.buffer[2], manual_menu1_l3);
  				 				strcpypgm2ram(oled.buffer[3], manual_menu1_l4);
								break;
		case manual_screen2:strcpypgm2ram(oled.buffer[0], manual_screen2_l1);
			 	 			strcpypgm2ram(oled.buffer[1], manual_screen2_l2);
  				 			strcpypgm2ram(oled.buffer[2], manual_screen2_l3);
  				 			strcpypgm2ram(oled.buffer[3], manual_screen2_l4);
							break;
		case manual_new1:	strcpypgm2ram(oled.buffer[0], manual_new1_l1);
			 	 			strcpypgm2ram(oled.buffer[1], manual_new1_l2);
  				 			strcpypgm2ram(oled.buffer[2], manual_new1_l3);
  				 			strcpypgm2ram(oled.buffer[3], manual_new1_l4);
							break;
		case manual_new2:	strcpypgm2ram(oled.buffer[0], manual_new2_l1);
			 	 			strcpypgm2ram(oled.buffer[1], manual_new2_l2);
  				 			strcpypgm2ram(oled.buffer[2], manual_new2_l3);
  				 			strcpypgm2ram(oled.buffer[3], manual_new2_l4);
							break;
		case manual_new_color:	strcpypgm2ram(oled.buffer[0], manual_new_color_l1);
			 	 				strcpypgm2ram(oled.buffer[1], manual_new_color_l2);
  				 				strcpypgm2ram(oled.buffer[2], manual_new_color_l3);
  				 				strcpypgm2ram(oled.buffer[3], manual_new_color_l4);
								// Insert code here to add the corresponding brightness of each color to the buffer //
								break;
		case manual_load1:	strcpypgm2ram(oled.buffer[0], manual_load1_l1);
			 	 			strcpypgm2ram(oled.buffer[1], manual_load1_l2);
  				 			strcpypgm2ram(oled.buffer[2], manual_load1_l3);
  				 			strcpypgm2ram(oled.buffer[3], manual_load1_l4);
							break;
		case manual_load2:	strcpypgm2ram(oled.buffer[0], manual_load2_l1);
			 	 			strcpypgm2ram(oled.buffer[1], manual_load2_l2);
  				 			strcpypgm2ram(oled.buffer[2], manual_load2_l3);
  				 			strcpypgm2ram(oled.buffer[3], manual_load2_l4);
							break;
		case manual_load3:	strcpypgm2ram(oled.buffer[0], manual_load3_l1);
			 	 			strcpypgm2ram(oled.buffer[1], manual_load3_l2);
  				 			strcpypgm2ram(oled.buffer[2], manual_load3_l3);
  				 			strcpypgm2ram(oled.buffer[3], manual_load3_l4);
							break;
		case manual_load4:	strcpypgm2ram(oled.buffer[0], manual_load4_l1);
			 	 			strcpypgm2ram(oled.buffer[1], manual_load4_l2);
  				 			strcpypgm2ram(oled.buffer[2], manual_load4_l3);
  				 			strcpypgm2ram(oled.buffer[3], manual_load4_l4);
							break;
	}
	
/*	// Clear the menu changed variable, buffer is now loaded.
	oled_changed = 0;

	// Set the buffer transfer variable.
	oled_buffer = 1;

	// Change the display pointer to the first location.
	oled.line = 0;
	oled.position = 0;
	cursor_moved = 1;
*/
	return;			   
}

void oled_load_adc(unsigned char dial1, unsigned char dial2)
{
	// Depending on which menu currently active, change the display and adjust settings
	// based on the coverted value.
	switch (oled.menu) {

		// Timeout Delay for Motion Sensors.
		case motion_menu2a:		
								// Dial 1.
								if (dial1 == 1) {									// 0%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_0);
									zone_timeout_delay = 0;							// 0s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '0';
									oled.buffer[0][19] = 's';
								} else if ((dial1 > 1) && (dial1 < 5)) {			// 2%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_2);
									zone_timeout_delay = 1;							// 0.1s
									oled.buffer[0][16] = '0';
									oled.buffer[0][17] = '.';
									oled.buffer[0][18] = '1';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 5) && (dial1 < 10)) {				// 4%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_4);
									zone_timeout_delay = 2;							// 0.2s
									oled.buffer[0][16] = '0';
									oled.buffer[0][17] = '.';
									oled.buffer[0][18] = '2';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 10) && (dial1 < 15)) {				// 6%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_6);
									zone_timeout_delay = 3;							// 0.3s
									oled.buffer[0][16] = '0';
									oled.buffer[0][17] = '.';
									oled.buffer[0][18] = '3';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 15) && (dial1 < 20)) {			// 8%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_8);
									zone_timeout_delay = 4;							// 0.4s
									oled.buffer[0][16] = '0';
									oled.buffer[0][17] = '.';
									oled.buffer[0][18] = '4';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 20) && (dial1 < 26)) {			// 10%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_10);
									zone_timeout_delay = 5;							// 0.5s
									oled.buffer[0][16] = '0';
									oled.buffer[0][17] = '.';
									oled.buffer[0][18] = '5';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 26) && (dial1 < 31)) {			// 12%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_12);
									zone_timeout_delay = 6;							// 0.6s
									oled.buffer[0][16] = '0';
									oled.buffer[0][17] = '.';
									oled.buffer[0][18] = '6';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 31) && (dial1 < 36)) {			// 14%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_14);
									zone_timeout_delay = 7;							// 0.7s
									oled.buffer[0][16] = '0';
									oled.buffer[0][17] = '.';
									oled.buffer[0][18] = '7';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 36) && (dial1 < 41)) {			// 16%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_16);
									zone_timeout_delay = 8;							// 0.8s
									oled.buffer[0][16] = '0';
									oled.buffer[0][17] = '.';
									oled.buffer[0][18] = '8';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 41) && (dial1 < 46)) {			// 18%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_18);
									zone_timeout_delay = 9;							// 0.9s
									oled.buffer[0][16] = '0';
									oled.buffer[0][17] = '.';
									oled.buffer[0][18] = '9';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 46) && (dial1 < 51)) {			// 20%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_20);
									zone_timeout_delay = 10;						// 1s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '1';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 51) && (dial1 < 56)) {			// 22%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_22);
									zone_timeout_delay = 20;						// 2s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '2';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 56) && (dial1 < 61)) {			// 24%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_24);
									zone_timeout_delay = 30;						// 3s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '3';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 61) && (dial1 < 66)) {			// 26%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_26);
									zone_timeout_delay = 40;						// 4s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '4';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 66) && (dial1 < 71)) {			// 28%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_28);
									zone_timeout_delay = 50;						// 5s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '5';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 71) && (dial1 < 77)) {			// 30%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_30);
									zone_timeout_delay = 60;						// 6s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '6';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 77) && (dial1 < 82)) {			// 32%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_32);
									zone_timeout_delay = 70;						// 7s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '7';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 82) && (dial1 < 87)) {			// 34%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_34);
									zone_timeout_delay = 80;						// 8s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '8';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 87) && (dial1 < 92)) {			// 36%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_36);
									zone_timeout_delay = 90;						// 9s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '9';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 92) && (dial1 < 97)) {			// 38%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_38);
									zone_timeout_delay = 100;						// 10s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '1';
									oled.buffer[0][18] = '0';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 97) && (dial1 < 102)) {			// 40%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_40);
									zone_timeout_delay = 120;						// 12s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '1';
									oled.buffer[0][18] = '2';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 102) && (dial1 < 107)) {		// 42%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_42);
									zone_timeout_delay = 140;						// 14s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '1';
									oled.buffer[0][18] = '4';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 107) && (dial1 < 112)) {		// 44%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_44);
									zone_timeout_delay = 160;						// 16s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '1';
									oled.buffer[0][18] = '6';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 112) && (dial1 < 117)) {		// 46%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_46);
									zone_timeout_delay = 180;						// 18s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '1';
									oled.buffer[0][18] = '8';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 117) && (dial1 < 122)) {		// 48%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_48);
									zone_timeout_delay = 200;						// 20s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '2';
									oled.buffer[0][18] = '0';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 122) && (dial1 < 128)) {		// 50%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_50);
									zone_timeout_delay = 220;						// 22s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '2';
									oled.buffer[0][18] = '2';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 128) && (dial1 < 133)) {		// 52%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_52);
									zone_timeout_delay = 240;						// 24s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '2';
									oled.buffer[0][18] = '4';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 133) && (dial1 < 138)) {		// 54%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_54);
									zone_timeout_delay = 260;						// 26s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '2';
									oled.buffer[0][18] = '6';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 138) && (dial1 < 143)) {		// 56%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_56);
									zone_timeout_delay = 280;						// 28s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '2';
									oled.buffer[0][18] = '8';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 143) && (dial1 < 148)) {		// 58%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_58);
									zone_timeout_delay = 300;						// 30s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '3';
									oled.buffer[0][18] = '0';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 148) && (dial1 < 153)) {		// 60%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_60);
									zone_timeout_delay = 350;						// 35s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '3';
									oled.buffer[0][18] = '5';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 153) && (dial1 < 158)) {		// 62%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_62);
									zone_timeout_delay = 400;						// 40s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '4';
									oled.buffer[0][18] = '0';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 158) && (dial1 < 163)) {		// 64%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_64);
									zone_timeout_delay = 450;						// 45s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '4';
									oled.buffer[0][18] = '5';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 163) && (dial1 < 168)) {		// 66%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_66);
									zone_timeout_delay = 500;						// 50s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '5';
									oled.buffer[0][18] = '0';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 168) && (dial1 < 173)) {		// 68%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_68);
									zone_timeout_delay = 550;						// 55s
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '5';
									oled.buffer[0][18] = '5';
									oled.buffer[0][19] = 's';
								} else if ((dial1 >= 173) && (dial1 < 179)) {		// 70%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_70);
									zone_timeout_delay = 600;						// 1m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '1';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 179) && (dial1 < 184)) {		// 72%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_72);
									zone_timeout_delay = 1200;						// 2m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '2';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 184) && (dial1 < 189)) {		// 74%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_74);
									zone_timeout_delay = 1800;						// 3m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '3';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 189) && (dial1 < 194)) {		// 76%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_76);
									zone_timeout_delay = 2400;						// 4m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '4';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 194) && (dial1 < 199)) {		// 78%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_78);
									zone_timeout_delay = 3000;						// 5m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '5';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 199) && (dial1 < 204)) {		// 80%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_80);
									zone_timeout_delay = 3600;						// 6m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '6';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 204) && (dial1 < 209)) {		// 82%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_82);
									zone_timeout_delay = 4200;						// 7m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '7';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 209) && (dial1 < 214)) {		// 84%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_84);
									zone_timeout_delay = 4800;						// 8m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '8';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 214) && (dial1 < 219)) {		// 86%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_86);
									zone_timeout_delay = 5400;						// 9m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = ' ';
									oled.buffer[0][18] = '9';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 219) && (dial1 < 224)) {		// 88%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_88);
									zone_timeout_delay = 6000;						// 10m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '1';
									oled.buffer[0][18] = '0';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 224) && (dial1 < 230)) {		// 90%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_90);
									zone_timeout_delay = 9000;						// 15m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '1';
									oled.buffer[0][18] = '5';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 230) && (dial1 < 235)) {		// 92%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_92);
									zone_timeout_delay = 12000;						// 20m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '2';
									oled.buffer[0][18] = '0';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 235) && (dial1 < 240)) {		// 94%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_94);
									zone_timeout_delay = 15000;						// 25m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '2';
									oled.buffer[0][18] = '5';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 240) && (dial1 < 245)) {		// 96%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_96);
									zone_timeout_delay = 18000;						// 30m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '3';
									oled.buffer[0][18] = '0';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 245) && (dial1 < 250)) {		// 98%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_98);
									zone_timeout_delay = 27000;						// 45m
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '4';
									oled.buffer[0][18] = '5';
									oled.buffer[0][19] = 'm';
								} else if ((dial1 >= 250) && (dial1 < 255)) {		// 100%
				 	 				strcpypgm2ram(oled.buffer[1], progress_bar_100);
									zone_timeout_delay = 36000;						// 1hr
									oled.buffer[0][16] = ' ';
									oled.buffer[0][17] = '1';
									oled.buffer[0][18] = 'h';
									oled.buffer[0][19] = 'r';
								}

								// Dial 2
								if (dial2 == 1) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_0);
									adjacent_brightness	= 0;
									adjacent2_brightness = 0;
								} else if ((dial2 > 1) && (dial2 < 5)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_2);
									adjacent_brightness	= 1;
									adjacent2_brightness = 0;
								} else if ((dial2 >= 5) && (dial2 < 10)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_4);
									adjacent_brightness	= 2;
									adjacent2_brightness = 0;
								} else if ((dial2 >= 10) && (dial2 < 15)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_6);
									adjacent_brightness	= 3;
									adjacent2_brightness = 0;
								} else if ((dial2 >= 15) && (dial2 < 20)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_8);
									adjacent_brightness	= 4;
									adjacent2_brightness = 0;
								} else if ((dial2 >= 20) && (dial2 < 26)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_10);
									adjacent_brightness	= 5;
									adjacent2_brightness = 0;
								} else if ((dial2 >= 26) && (dial2 < 31)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_12);
									adjacent_brightness	= 6;
									adjacent2_brightness = 0;
								} else if ((dial2 >= 31) && (dial2 < 36)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_14);
									adjacent_brightness	= 7;
									adjacent2_brightness = 0;
								} else if ((dial2 >= 36) && (dial2 < 41)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_16);
									adjacent_brightness	= 8;
									adjacent2_brightness = 0;
								} else if ((dial2 >= 41) && (dial2 < 46)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_18);
									adjacent_brightness	= 9;
									adjacent2_brightness = 0;
								} else if ((dial2 >= 46) && (dial2 < 51)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_20);
									adjacent_brightness	= 10;
									adjacent2_brightness = 0;
								} else if ((dial2 >= 51) && (dial2 < 56)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_22);
										adjacent_brightness	= 12;
									adjacent2_brightness = 1;
								} else if ((dial2 >= 56) && (dial2 < 61)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_24);
									adjacent_brightness	= 14;
									adjacent2_brightness = 2;
								} else if ((dial2 >= 61) && (dial2 < 66)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_26);
									adjacent_brightness	= 16;
									adjacent2_brightness = 3;
								} else if ((dial2 >= 66) && (dial2 < 71)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_28);
									adjacent_brightness	= 18;
									adjacent2_brightness = 4;
								} else if ((dial2 >= 71) && (dial2 < 77)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_30);
									adjacent_brightness	= 20;
									adjacent2_brightness = 5;
								} else if ((dial2 >= 77) && (dial2 < 82)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_32);
									adjacent_brightness	= 22;
									adjacent2_brightness = 6;
								} else if ((dial2 >= 82) && (dial2 < 87)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_34);
									adjacent_brightness	= 24;
									adjacent2_brightness = 7;
								} else if ((dial2 >= 87) && (dial2 < 92)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_36);
									adjacent_brightness	= 26;
									adjacent2_brightness = 8;
								} else if ((dial2 >= 92) && (dial2 < 97)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_38);
									adjacent_brightness	= 28;
									adjacent2_brightness = 9;
								} else if ((dial2 >= 97) && (dial2 < 102)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_40);
									adjacent_brightness	= 30;
									adjacent2_brightness = 10;
								} else if ((dial2 >= 102) && (dial2 < 107)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_42);
									adjacent_brightness	= 35;
									adjacent2_brightness = 12;
								} else if ((dial2 >= 107) && (dial2 < 112)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_44);
									adjacent_brightness	= 40;
									adjacent2_brightness = 14;
								} else if ((dial2 >= 112) && (dial2 < 117)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_46);
									adjacent_brightness	= 45;
									adjacent2_brightness = 16;
								} else if ((dial2 >= 117) && (dial2 < 122)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_48);
									adjacent_brightness	= 50;
									adjacent2_brightness = 18;
								} else if ((dial2 >= 122) && (dial2 < 128)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_50);
									adjacent_brightness	= 55;
									adjacent2_brightness = 20;
								} else if ((dial2 >= 128) && (dial2 < 133)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_52);
									adjacent_brightness	= 60;
									adjacent2_brightness = 22;
								} else if ((dial2 >= 133) && (dial2 < 138)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_54);
									adjacent_brightness	= 65;
									adjacent2_brightness = 24;
								} else if ((dial2 >= 138) && (dial2 < 143)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_56);
									adjacent_brightness	= 70;
									adjacent2_brightness = 26;
								} else if ((dial2 >= 143) && (dial2 < 148)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_58);
									adjacent_brightness	= 75;
									adjacent2_brightness = 28;
								} else if ((dial2 >= 148) && (dial2 < 153)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_60);
									adjacent_brightness	= 80;
									adjacent2_brightness = 30;
								} else if ((dial2 >= 153) && (dial2 < 158)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_62);
									adjacent_brightness	= 85;
									adjacent2_brightness = 35;
								} else if ((dial2 >= 158) && (dial2 < 163)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_64);
									adjacent_brightness	= 90;
									adjacent2_brightness = 40;
								} else if ((dial2 >= 163) && (dial2 < 168)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_66);
									adjacent_brightness	= 95;
									adjacent2_brightness = 45;
								} else if ((dial2 >= 168) && (dial2 < 173)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_68);
									adjacent_brightness	= 100;
									adjacent2_brightness = 50;
								} else if ((dial2 >= 173) && (dial2 < 179)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_70);
									adjacent_brightness	= 100;
									adjacent2_brightness = 55;
								} else if ((dial2 >= 179) && (dial2 < 184)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_72);
									adjacent_brightness	= 100;
									adjacent2_brightness = 60;
								} else if ((dial2 >= 184) && (dial2 < 189)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_74);
									adjacent_brightness	= 100;
									adjacent2_brightness = 65;
								} else if ((dial2 >= 189) && (dial2 < 194)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_76);
									adjacent_brightness	= 100;
									adjacent2_brightness = 70;
								} else if ((dial2 >= 194) && (dial2 < 199)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_78);
									adjacent_brightness	= 100;
									adjacent2_brightness = 75;
								} else if ((dial2 >= 199) && (dial2 < 204)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_80);
									adjacent_brightness	= 100;
									adjacent2_brightness = 80;
								} else if ((dial2 >= 204) && (dial2 < 209)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_82);
									adjacent_brightness	= 100;
									adjacent2_brightness = 85;
								} else if ((dial2 >= 209) && (dial2 < 214)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_84);
									adjacent_brightness	= 100;
									adjacent2_brightness = 90;
								} else if ((dial2 >= 214) && (dial2 < 219)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_86);
									adjacent_brightness	= 100;
									adjacent2_brightness = 95;
								} else if ((dial2 >= 219) && (dial2 < 224)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_88);
									adjacent_brightness	= 100;
									adjacent2_brightness = 100;
								} else if ((dial2 >= 224) && (dial2 < 230)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_90);
									adjacent_brightness	= 100;
									adjacent2_brightness = 100;
								} else if ((dial2 >= 230) && (dial2 < 235)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_92);
									adjacent_brightness	= 100;
									adjacent2_brightness = 100;
								} else if ((dial2 >= 235) && (dial2 < 240)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_94);
									adjacent_brightness	= 100;
									adjacent2_brightness = 100;
								} else if ((dial2 >= 240) && (dial2 < 245)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_96);
									adjacent_brightness	= 100;
									adjacent2_brightness = 100;
								} else if ((dial2 >= 245) && (dial2 < 250)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_98);
									adjacent_brightness	= 100;
									adjacent2_brightness = 100;
								} else if ((dial2 >= 250) && (dial2 < 255)) {
				 	 				strcpypgm2ram(oled.buffer[3], progress_bar_100);
									adjacent_brightness	= 100;
									adjacent2_brightness = 100;
								}	
								break;
	}	

}

/*  Sends a command to the OLED to move the cursor.
 *  Moves the cursor on the OLED to the position and line in the oled.line and
 *  oled.position registers.
 */
void oled_move_cursor(void)
{
	// Move the cursor to the appropriate position.
	switch (oled.line) {
		case 0:	oled_send_command(0, 0, oled.position + 0x80);
				break;
		case 1: oled_send_command(0, 0, oled.position + 0xC0);
				break;
		case 2: oled_send_command(0, 0, oled.position + 0x94);
				break;
		case 3: oled_send_command(0, 0, oled.position + 0xD4);
				break;
	}
}

/*  Creates a custom character 
 *  This function creates the custom character that is used for the arrow in the OLED
 *  menu. The character is stored in location oled_cursor_address (0x78) and can be
 *  printed with the character oled_cursor (0x07).
 */
void oled_create_custom_cursor(void)
{
	while (!oled_ready);		// Wait for the OLED to be ready for a command.

	// Go to the first location of the 8th custom character to start writing the symbol out.
	oled_send_command( 0, 0, 0x78);

	while (!oled_ready);

	oled_print(0x00);			//  				
	while(!oled_ready);				
	oled_print(0x08);			//		1			
	while(!oled_ready);
	oled_print(0x0C);			//		1	1		
	while(!oled_ready);
	oled_print(0x1E);			//	1	1	1	1	
	while(!oled_ready);
	oled_print(0x1F);			//	1	1	1	1	1
	while(!oled_ready);
	oled_print(0x1E);			//	1	1	1	1	
	while(!oled_ready);
	oled_print(0x0C);			//		1	1		
	while(!oled_ready);
	oled_print(0x08);			//		1			

}

/*  This function creates the custom characters used for the loading bar.  There is a 
 *  1, 2, 3, 4 and 5 line symbol that displays increase from left to right.  The characters
 *  are stored in the locations (0x28) thru (0x68) and can be printed with oled_load1 thru
 *  oled_load5.
 */
void oled_create_custom_load(void)
{
	while (!oled_ready);		// Wait for the OLED to be ready for a command.

	// Loading Bar 1
	oled_send_command( 0, 0, 0x50);

	while (!oled_ready);

	oled_print(0x10);			//  1				
	while(!oled_ready);				
	oled_print(0x10);			//	1				
	while(!oled_ready);
	oled_print(0x10);			//	1				
	while(!oled_ready);
	oled_print(0x10);			//	1				
	while(!oled_ready);
	oled_print(0x10);			//	1				
	while(!oled_ready);
	oled_print(0x10);			//	1				
	while(!oled_ready);
	oled_print(0x10);			//	1				
	while(!oled_ready);
	oled_print(0x10);			//	1	

	while (!oled_ready);		// Wait for the OLED to be ready for a command.

	// Loading Bar 2
//	oled_send_command( 0, 0, 0x38);

//	while (!oled_ready);

	oled_print(0x18);			//  1	1				
	while(!oled_ready);				
	oled_print(0x18);			//	1	1				
	while(!oled_ready);
	oled_print(0x18);			//	1	1			
	while(!oled_ready);
	oled_print(0x18);			//	1	1			
	while(!oled_ready);
	oled_print(0x18);			//	1	1			
	while(!oled_ready);
	oled_print(0x18);			//	1	1			
	while(!oled_ready);
	oled_print(0x18);			//	1	1			
	while(!oled_ready);
	oled_print(0x18);			//	1	1		

	while (!oled_ready);		// Wait for the OLED to be ready for a command.

	// Loading Bar 3
//	oled_send_command( 0, 0, 0x48);

//	while (!oled_ready);

	oled_print(0x1C);			//  1	1	1			
	while(!oled_ready);				
	oled_print(0x1C);			//	1	1	1			
	while(!oled_ready);
	oled_print(0x1C);			//	1	1	1		
	while(!oled_ready);
	oled_print(0x1C);			//	1	1	1		
	while(!oled_ready);
	oled_print(0x1C);			//	1	1	1		
	while(!oled_ready);
	oled_print(0x1C);			//	1	1	1		
	while(!oled_ready);
	oled_print(0x1C);			//	1	1	1		
	while(!oled_ready);
	oled_print(0x1C);			//	1	1	1

	while (!oled_ready);		// Wait for the OLED to be ready for a command.

	// Loading Bar 4
//	oled_send_command( 0, 0, 0x58);

//	while (!oled_ready);

	oled_print(0x1E);			//  1	1	1	1		
	while(!oled_ready);				
	oled_print(0x1E);			//	1	1	1	1		
	while(!oled_ready);
	oled_print(0x1E);			//	1	1	1	1	
	while(!oled_ready);
	oled_print(0x1E);			//	1	1	1	1	
	while(!oled_ready);
	oled_print(0x1E);			//	1	1	1	1	
	while(!oled_ready);
	oled_print(0x1E);			//	1	1	1	1	
	while(!oled_ready);
	oled_print(0x1E);			//	1	1	1	1	
	while(!oled_ready);
	oled_print(0x1E);			//	1	1	1	1

	while (!oled_ready);		// Wait for the OLED to be ready for a command.

	// Loading Bar 5
//	oled_send_command( 0, 0, 0x68);

//	while (!oled_ready);

	oled_print(0x1F);			//  1	1	1	1	1	
	while(!oled_ready);				
	oled_print(0x1F);			//	1	1	1	1	1	
	while(!oled_ready);
	oled_print(0x1F);			//	1	1	1	1	1
	while(!oled_ready);
	oled_print(0x1F);			//	1	1	1	1	1
	while(!oled_ready);
	oled_print(0x1F);			//	1	1	1	1	1
	while(!oled_ready);
	oled_print(0x1F);			//	1	1	1	1	1
	while(!oled_ready);
	oled_print(0x1F);			//	1	1	1	1	1
	while(!oled_ready);
	oled_print(0x1F);			//	1	1	1	1	1				

}

/*  Sends a command to the OLED Display.
 *  This function passes unsigned int 'rs' and 'rw' and unsigned char 'command' that is to
 *  be sent to the display.  The function sends: RS, RW, B7, B6, B5, B4, B3, B2, B1, B0.
 *  The delays are: 200-250 ns data setup to clock in.
 *  				250 ns clock pulse width.
 *					800 ns cycle time.
 *					9.5 us function time.
 *  CS is returned high at the end of the function.
 */
void oled_send_command(unsigned int rs, unsigned int rw, unsigned char command)
{
	union command_data oled_command;
	unsigned char highh = 0xF0;
	unsigned char highl = 0x60;
	unsigned char lowh = 0xF9;
	unsigned char lowl = 0xC0;

	oled_command.byte = command;

	INTCONbits.GIE = 0;			// Disable all interrupts while sending data to OLED.

	Nop();
	Nop();
	sck = 1;
	Nop();
	scs = 0;				// Set Chip Select low to start transmission.
	Nop();
	Nop();
	sck = 0;				// Set clock low to get ready to clock data in.
	sdo = rs;				// Send RS out the data line.
	Nop();
	sck = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = rw;				// Send RW out the data line.
	Nop();
	sck = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b7;
	Nop();
	sck = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b6;
	Nop();
	sck = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b5;
	Nop();
	sck = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b4;
	Nop();
	sck = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b3;
	Nop();
	sck = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b2;
	Nop();
	sck = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b1;
	Nop();
	sck = 1;				// Clock in the data.
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b0;
	Nop();
	sck = 1;				// Clock in the data.
	Nop();
	scs = 1;

	// OLED not ready for more data.
	oled_ready = 0;	

	// If the command is a reset, initiate a high (2ms) delay.
	// Otherwise intiate a low (800us) delay.
	if (oled_command.byte == 0x01) {
		TMR3H = highh;
		TMR3L = highl;
	} else {
		TMR3H = lowh;
		TMR3L = lowl;
	}

	// Start Timer for OLED to be ready to receive more data.
	oled_timer = 1;

	INTCONbits.GIE = 1;			// Enable interrupts after data is sent..

}


/*  Print a character to the OLED Display.
 *  This function prints the unsigned char passed into the function out to the OLED.
 *  This function assumes this character is going into DDRAM and will be a displayable
 *  character.  This function automatically prints RS = 1 and RW = 0.  Then it prints
 *  the unsigned char bits: B7, B6, B5, B4, B3, B2, B1, B0.
 *  The delays are: 200-250 ns data setup to clock in.
 *  				250 ns clock pulse width.
 *					800 ns cycle time.
 *					9.5 us function time.
 *  CS is returned high at the end of the function.
 */
void oled_print(unsigned char char_data)
{
	union command_data oled_data;

	oled_data.byte = char_data;

	INTCONbits.GIE = 0;			// Disable all interrupts while sending data to OLED.

		Nop();
		Nop();
		sck = 1;
		Nop();
		scs = 0;				// Set Chip Select low to start transmission.
		Nop();
		Nop();
		sck = 0;				// Set clock low to get ready to clock data in.
		sdo = 1;				// RS = 1.
		Nop();					
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = 0;				// RW = 0.
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b7;
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b6;
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b5;
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b4;
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b3;
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b2;
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b1;
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b0;
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		scs = 1;

	// OLED not ready for more data.
	oled_ready = 0;	

	// Initiate a low (800us) delay.
	TMR3H = 0xF9;
	TMR3L = 0xC0;

	// Start Timer for OLED to be ready to receive more data.
	oled_timer = 1;

	INTCONbits.GIE = 1;			// Enable all interrupts after data is sent to OLED.

}

