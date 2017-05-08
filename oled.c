
/*****************************************************************************************
 *                                      OLED											 *
 *****************************************************************************************/

/*  Root function for processing OLED.
 */
void strobe_oled(unsigned char oled_process, unsigned char dial1, unsigned char dial2)
{
	static unsigned char new_data = 0;

	// Variable passed into the function decides which process is completed.
	// 1 - Load the oled buffer with new menu data.
	// 2 - Load the oled buffer with the selected zone being changed adjusted.
	// 3 - General operation.
	switch (oled_process) {

		// Load buffer with new menu data.
		case oled_menu:	{

							oled_load_menu();			
			
						} break;

		// Load buffer with new selected zone.
		case oled_zone: {

							oled_load_zone();

						} break;

		// Send buffer data to the OLED.
		case oled_run: {

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
 *  until it finds a location that has new data.  When the function finishes checking
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
			// >>> Line 1.
			case 0: { 
						oled.line = 1;
					} break;
			// >>> Line 2.
			case 1: { 
						oled.line = 2;
					} break;
			// >>> Line 3.
			case 2: { 
						oled.line = 3;
					} break;
			// >>> Line 0.
			case 3: { 
						oled.line = 0;
					} break;
			
			// Error.  >>> Line 0.
			default: { 
					oled.line = 0;
				} break;
		}

		strobe_lights(led_run);			// Check the lights.

		oled.position = 0;				// >>> Position 0.
		
		oled_move_cursor();				// Move the cursor.
		
		return;
	}

	strobe_lights(led_run);				// Check the lights.

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
	unsigned char *ptr1 = 0;
	unsigned char *ptr2 = 0;
	unsigned char i;
	unsigned char name_length = 0;
	unsigned int z;


	switch (oled.menu) {

		// Welcome Screen
		case welcome_screen1:  	strcpypgm2ram((char *)oled.buffer[0], welcome_screen1_l1);	// Set the screen to the welcome screen
			 	 				strcpypgm2ram((char *)oled.buffer[1], welcome_screen1_l2);	// with the name of the device, version
  				 				strcpypgm2ram((char *)oled.buffer[2], welcome_screen1_l3);	// number and writer.
  				 				strcpypgm2ram((char *)oled.buffer[3], welcome_screen1_l4);
				 				break;

		// Change Color
		case strobe_short_new3:
		case strobe_long_new3:
		case manual_menu2:		strcpypgm2ram((char *)oled.buffer[0], change_color_l1);
			 	 				strcpypgm2ram((char *)oled.buffer[1], change_color_l2);
  				 				strcpypgm2ram((char *)oled.buffer[2], change_color_l3);
  				 				strcpypgm2ram((char *)oled.buffer[3], change_color_l4);
								oled.buffer[0][1] = oled_cursor;							// Point the cursor at Zone.

								switch (oled.menu) {

									case manual_menu2: 	oled.menu = manual_menu2a;	
														break;
									case manual_save2:	oled.menu = manual_save2a;
														strobe_mem(mem_manual_load_names, 0, 0);
														break;
								}

								break;

		// Memory Slot
		case strobe_short_save_name:
		case strobe_long_save_name:
		case strobe_short_load1:
		case strobe_long_load1:
		case strobe_short_new1:
		case strobe_long_new1:
		case manual_save2:
		case manual_menu3:		strcpypgm2ram((char *)oled.buffer[0], memory_slot_l1);
				 	 			strcpypgm2ram((char *)oled.buffer[1], memory_slot_l2);
	  				 			strcpypgm2ram((char *)oled.buffer[2], memory_slot_l3);
	  				 			strcpypgm2ram((char *)oled.buffer[3], memory_slot_l4);	
								oled.buffer[0][1] = oled_cursor;							// Point the cursor at Slot 1.

								switch (oled.menu) {

									case manual_menu3: 		oled.menu = manual_menu3a;
															strobe_mem(mem_manual_load_names, 0, 0);	
															break;

									case manual_save2:		oled.menu = manual_save2a;
															strobe_mem(mem_manual_load_names, 0, 0);
															break;

									case strobe_short_load1:oled.menu = strobe_short_load1a;
															strobe_mem(mem_strobe_short_load_names, 0, 0);
															break;

									case strobe_short_new1:	oled.menu = strobe_short_new1a;
															strobe_mem(mem_strobe_short_load_names, 0, 0);
															break;

									case strobe_long_load1:oled.menu = strobe_long_load1a;
															strobe_mem(mem_strobe_long_load_names, 0, 0);
															break;

									case strobe_long_new1:	oled.menu = strobe_long_new1a;
															strobe_mem(mem_strobe_long_load_names, 0, 0);
															break;

									case strobe_short_save_name:	switch (stage_save_slot) {

																		case 2:	oled.buffer[1][1] = oled_cursor;	// Point the cursor at Slot 2.
																				oled.buffer[0][1] = oled_space;
																				break;
																		case 3:	oled.buffer[2][1] = oled_cursor;	// Point the cursor at Slot 3.
																				oled.buffer[0][1] = oled_space;
																				break;
																		case 4:	oled.buffer[3][1] = oled_cursor;	// Point the cursor at Slot 4.
																				oled.buffer[0][1] = oled_space;
																				break;
																	}
																	strobe_mem(mem_strobe_short_load_names, 0, 0);	
															break;

									case strobe_long_save_name:		switch (stage_save_slot) {				

																		case 6:	oled.buffer[1][1] = oled_cursor;	// Point the cursor at Slot 2.
																				oled.buffer[0][1] = oled_space;
																				break;
																		case 7:	oled.buffer[2][1] = oled_cursor;	// Point the cursor at Slot 3.
																				oled.buffer[0][1] = oled_space;
																				break;
																		case 8:	oled.buffer[3][1] = oled_cursor;	// Point the cursor at Slot 4.
																				oled.buffer[0][1] = oled_space;
																				break;
																	}		
																	strobe_mem(mem_strobe_long_load_names, 0, 0);				
															break;
								}
								break;

		// Select Menu 1
		// Cursor > Motion Sensing
		case select_menu1a:		strcpypgm2ram((char *)oled.buffer[0], select_menu1_l1);		// Set the screen to Select Menu 1
			 	 				strcpypgm2ram((char *)oled.buffer[1], select_menu1_l2);		// Motion Sensing, Manual, STROBE, Next.
  				 				strcpypgm2ram((char *)oled.buffer[2], select_menu1_l3);
  				 				strcpypgm2ram((char *)oled.buffer[3], select_menu1_l4);
								oled.buffer[0][2] = oled_cursor;					// Point the cursor at Motion Sensing.
								break;

		// Cursor > Manual
		case select_menu1b:		oled.buffer[1][2] = oled_cursor;					// Point the cursor at Manual.
								oled.buffer[0][2] = oled_space;
								oled.buffer[2][2] = oled_space;
								break;

		// Cursor > STROBE
		case select_menu1c:		oled.buffer[2][2] = oled_cursor;					// Point the cursor at STROBE.
								oled.buffer[1][2] = oled_space;
								oled.buffer[3][12] = oled_space;
								oled.buffer[0][2] = oled_space;	
								break;

		// Motion Menu 1
		// Initial
		case motion_menu1:		strcpypgm2ram((char *)oled.buffer[0], motion_menu1_l1);
				 	 			strcpypgm2ram((char *)oled.buffer[1], motion_menu1_l2);
	  				 			strcpypgm2ram((char *)oled.buffer[2], motion_menu1_l3);
	  				 			strcpypgm2ram((char *)oled.buffer[3], motion_menu1_l4);
								oled.buffer[0][2] = oled_cursor;					// Point the cursor at Start.
								break;

		// Cursor > Start
		// Off
		case motion_menu1a_off:	strcpypgm2ram((char *)oled.buffer[0], motion_menu1a_off_l1);
	  				 			strcpypgm2ram((char *)oled.buffer[3], motion_menu1a_off_l4);
								oled.buffer[0][2] = oled_cursor;					// Point the cursor at Start.
								oled.buffer[1][2] = oled_space;
								oled.buffer[2][2] = oled_space;
								break;

		// Cursor > Stop
		// On
		case motion_menu1a_on:	strcpypgm2ram((char *)oled.buffer[0], motion_menu1a_on_l1);
	  				 			strcpypgm2ram((char *)oled.buffer[3], motion_menu1a_on_l4);				
								oled.buffer[0][2] = oled_cursor;					// Point the cursor at Stop.
								oled.buffer[1][2] = oled_space;
								oled.buffer[2][2] = oled_space;
								break;

		// Cursor > Options
		case motion_menu1b:		oled.buffer[1][2] = oled_cursor;					// Point the cursor at Timeout Delay.
								oled.buffer[0][2] = oled_space;
								oled.buffer[2][2] = oled_space;
								break;

		// Cursor > Tracking
		// On
		case motion_menu1c_on:	strcpypgm2ram((char *)oled.buffer[2], motion_menu1c_on_l3);			
								oled.buffer[2][2] = oled_cursor;					// Point the cursor at Tracking.
								oled.buffer[1][2] = oled_space;
								oled.buffer[0][2] = oled_space;
								break;

		// Cursor > Tracking
		// Off
		case motion_menu1c_off:	strcpypgm2ram((char *)oled.buffer[2], motion_menu1c_off_l3);			
								oled.buffer[2][2] = oled_cursor;					// Point the cursor at Tracking.
								oled.buffer[1][2] = oled_space;
								oled.buffer[0][2] = oled_space;
								break;

		// Motion Menu 2
		case motion_menu2a:		strcpypgm2ram((char *)oled.buffer[0], motion_menu2_l1);
				 	 			strcpypgm2ram((char *)oled.buffer[1], motion_menu2_l2);
	  				 			strcpypgm2ram((char *)oled.buffer[2], motion_menu2_l3);
	  				 			strcpypgm2ram((char *)oled.buffer[3], motion_menu2_l4);	
								break;

		// Manual Menu 1
		case manual_menu1a:		strcpypgm2ram((char *)oled.buffer[0], manual_menu1_l1);
			 	 				strcpypgm2ram((char *)oled.buffer[1], manual_menu1_l2);
  				 				strcpypgm2ram((char *)oled.buffer[2], manual_menu1_l3);
  				 				strcpypgm2ram((char *)oled.buffer[3], manual_menu1_l4);
								oled.buffer[1][1] = oled_cursor;					// Point the cursor at New.
								break;

		// Cursor > Load
		case manual_menu1b:		oled.buffer[2][1] = oled_cursor;					// Point the cursor at Load.
								oled.buffer[1][1] = oled_space;					
								break;

		// Manual Menu 2
		// Cursor > Zone
		case manual_menu2a:		oled.buffer[0][1] = oled_cursor;					// Point the cursor at Zone.
								oled.buffer[1][1] = oled_space;	
								oled.buffer[3][1] = oled_space;					
								break;

		// Select > Zone
		case manual_menu2a_zone:oled.buffer[0][1] = oled_space;
								break;

		// Cursor > Red
		case manual_menu2b:		oled.buffer[1][1] = oled_cursor;					// Point the cursor at Red.
								oled.buffer[0][1] = oled_space;
								oled.buffer[2][1] = oled_space;						
								break;

		// Select > Red
		case manual_menu2b_red:	oled.buffer[1][1] = oled_space;
								break;

		// Cursor > Green
		case manual_menu2c:		oled.buffer[2][1] = oled_cursor;					// Point the cursor at Green.
								oled.buffer[1][1] = oled_space;
								oled.buffer[3][1] = oled_space;						
								break;

		// Select > Green
		case manual_menu2c_green:oled.buffer[2][1] = oled_space;
								break;

		// Cursor > Blue
		case manual_menu2d:		oled.buffer[3][1] = oled_cursor;					// Point the cursor at Blue.
								oled.buffer[2][1] = oled_space;	
								oled.buffer[0][1] = oled_space;	
								break;

		// Select > Blue
		case manual_menu2d_blue:oled.buffer[3][1] = oled_space;
								break;

		// Manual Menu 3
		// Cursor > Slot 1
		case manual_menu3a:		oled.buffer[0][1] = oled_cursor;					// Point the cursor at Slot 2.
								oled.buffer[1][1] = oled_space;	
								oled.buffer[3][1] = oled_space;	
								break;

		// Cursor > Slot 2
		case manual_menu3b:		oled.buffer[1][1] = oled_cursor;					// Point the cursor at Slot 2.
								oled.buffer[0][1] = oled_space;	
								oled.buffer[2][1] = oled_space;	
								break;

		// Cursor > Slot 3
		case manual_menu3c:		oled.buffer[2][1] = oled_cursor;					// Point the cursor at Slot 3.
								oled.buffer[1][1] = oled_space;	
								oled.buffer[3][1] = oled_space;	
								break;

		// Cursor > Slot 4
		case manual_menu3d:		oled.buffer[3][1] = oled_cursor;					// Point the cursor at Slot 4.
								oled.buffer[2][1] = oled_space;	
								oled.buffer[0][1] = oled_space;	
								break;

		// Manual Save 1
		case manual_save1a:		strcpypgm2ram((char *)oled.buffer[0], manual_save1_l1);
				 	 			strcpypgm2ram((char *)oled.buffer[1], manual_save1_l2);
	  				 			strcpypgm2ram((char *)oled.buffer[2], manual_save1_l3);
	  				 			strcpypgm2ram((char *)oled.buffer[3], manual_save1_l4);	
								oled.buffer[2][7] = oled_cursor;					// Point the cursor at Yes.			
								break;

		// Cursor > No
		case manual_save1b:		oled.buffer[3][7] = oled_cursor;					// Point the cursor at No.
								oled.buffer[2][7] = oled_space;	
								break;

		// Manual Save 2
		// Cursor > Slot 1
		case manual_save2a:		oled.buffer[0][1] = oled_cursor;					// Point the cursor at Slot 2.
								oled.buffer[1][1] = oled_space;	
								oled.buffer[3][1] = oled_space;		
								break;

		// Cursor > Slot 2
		case manual_save2b:		oled.buffer[1][1] = oled_cursor;					// Point the cursor at Slot 2.
								oled.buffer[0][1] = oled_space;	
								oled.buffer[2][1] = oled_space;	
								break;

		// Cursor > Slot 3
		case manual_save2c:		oled.buffer[2][1] = oled_cursor;					// Point the cursor at Slot 3.
								oled.buffer[1][1] = oled_space;	
								oled.buffer[3][1] = oled_space;	
								break;

		// Cursor > Slot 4
		case manual_save2d:		oled.buffer[3][1] = oled_cursor;					// Point the cursor at Slot 4.
								oled.buffer[2][1] = oled_space;	
								oled.buffer[0][1] = oled_space;	
								break;

		// STROBE Menu 1
		// Cursor > Short Show
		case strobe_menu1a:		strcpypgm2ram((char *)oled.buffer[0], strobe_menu1_l1);
				 	 			strcpypgm2ram((char *)oled.buffer[1], strobe_menu1_l2);
	  				 			strcpypgm2ram((char *)oled.buffer[2], strobe_menu1_l3);
	  				 			strcpypgm2ram((char *)oled.buffer[3], strobe_menu1_l4);	
								oled.buffer[1][1] = oled_cursor;					// Point the cursor at Short Show.			
								break;

		// Cursor > Long Show
		case strobe_menu1b:		oled.buffer[1][1] = oled_space;	
								oled.buffer[2][1] = oled_cursor;					// Point the cursor at Long Show.
								oled.buffer[3][1] = oled_space;				
								break;

		// Cursor > Strobe Light
		case strobe_menu1c:		oled.buffer[2][1] = oled_space;	
								oled.buffer[3][1] = oled_cursor;					// Point the cursor at Strobe Light.
								oled.buffer[1][1] = oled_space;	
								break;

		// STROBE Short Menu 1
		// Cursor > New
		case strobe_short1a:	strcpypgm2ram((char *)oled.buffer[0], strobe_short1_l1);
				 	 			strcpypgm2ram((char *)oled.buffer[1], strobe_short1_l2);
	  				 			strcpypgm2ram((char *)oled.buffer[2], strobe_short1_l3);
	  				 			strcpypgm2ram((char *)oled.buffer[3], strobe_short1_l4);	
								oled.buffer[1][1] = oled_cursor;					// Point the cursor at New.			
								break;

		// Cursor > Load
		case strobe_short1b:	oled.buffer[1][1] = oled_space;	
								oled.buffer[2][1] = oled_cursor;					// Point the cursor at Load.			
								break;

		// STROBE SHORT NEW Menu 1
		// Cursor > Slot 1
		case strobe_short_new1a:	oled.buffer[0][1] = oled_cursor;				// Point the cursor at Slot 1.
									oled.buffer[1][1] = oled_space;	
									oled.buffer[3][1] = oled_space;	
									break;

		// Cursor > Slot 2
		case strobe_short_new1b:	oled.buffer[1][1] = oled_cursor;				// Point the cursor at Slot 2.
									oled.buffer[2][1] = oled_space;
									oled.buffer[0][1] = oled_space;								
									break;

		// Cursor > Slot 3
		case strobe_short_new1c:	oled.buffer[2][1] = oled_cursor;				// Point the cursor at Slot 3.
									oled.buffer[1][1] = oled_space;
									oled.buffer[3][1] = oled_space;								
									break;

		// Cursor > Slot 4
		case strobe_short_new1d:	oled.buffer[3][1] = oled_cursor;				// Point the cursor at Slot 4.
									oled.buffer[2][1] = oled_space;
									oled.buffer[0][1] = oled_space;									
									break;

		// STROBE SHORT NEW Menu 2
		// Initial
		case strobe_short_new2:	strcpypgm2ram((char *)oled.buffer[0], strobe_short_new2_l1);
				 	 			strcpypgm2ram((char *)oled.buffer[1], strobe_short_new2_l2);
	  				 			strcpypgm2ram((char *)oled.buffer[2], strobe_short_new2_l3);
	  				 			strcpypgm2ram((char *)oled.buffer[3], strobe_short_new2_l4);
								// Write out the stage number.
								z = ((float)stage_save_count * 0.1);
								if (z > 0) {
									oled.buffer[0][10] = z + 0x30;
								}
								z = stage_save_count - (z * 10);
								oled.buffer[0][11] = z + 0x30;		
								break;

		// Cursor > Change Colors
		case strobe_short_new2a:oled.buffer[1][1] = oled_cursor;				
								oled.buffer[2][1] = oled_space;	
								oled.buffer[3][14] = oled_space;			
								break;

		// Cursor > Change Timing
		case strobe_short_new2b:oled.buffer[2][1] = oled_cursor;
								oled.buffer[1][1] = oled_space;	
								oled.buffer[3][0] = oled_space;			
								break;

		// Cursor > Next
		case strobe_short_new2c:oled.buffer[3][0] = oled_cursor;
								oled.buffer[2][1] = oled_space;	
								oled.buffer[1][0] = oled_space;	
								oled.buffer[3][7] = oled_space;		
								break;

		// Cursor > Back
		case strobe_short_new2d:oled.buffer[3][7] = oled_cursor;
								oled.buffer[3][0] = oled_space;	
								oled.buffer[1][0] = oled_space;	
								oled.buffer[3][14] = oled_space;		
								break;

		// Cursor > Done
		case strobe_short_new2e:oled.buffer[3][14] = oled_cursor;
								oled.buffer[3][7] = oled_space;	
								oled.buffer[1][1] = oled_space;			
								break;

		// STROBE Short New 3
		// Cursor > Zone
		case strobe_short_new3a:		oled.buffer[0][1] = oled_cursor;
										oled.buffer[1][1] = oled_space;	
										oled.buffer[3][1] = oled_space;					
										break;

		// Select > Zone
		case strobe_short_new3a_zone:	oled.buffer[0][1] = oled_space;
										break;

		// Cursor > Red
		case strobe_short_new3b:		oled.buffer[1][1] = oled_cursor;
										oled.buffer[0][1] = oled_space;
										oled.buffer[2][1] = oled_space;						
										break;

		// Select > Red
		case strobe_short_new3b_red:	oled.buffer[1][1] = oled_space;
										break;

		// Cursor > Green
		case strobe_short_new3c:		oled.buffer[2][1] = oled_cursor;
										oled.buffer[1][1] = oled_space;
										oled.buffer[3][1] = oled_space;						
										break;

		// Select > Green
		case strobe_short_new3c_green:	oled.buffer[2][1] = oled_space;
										break;

		// Cursor > Blue
		case strobe_short_new3d:		oled.buffer[3][1] = oled_cursor;
										oled.buffer[2][1] = oled_space;	
										oled.buffer[0][1] = oled_space;	
										break;

		// Select > Blue
		case strobe_short_new3d_blue:	oled.buffer[3][1] = oled_space;
										break;

		// STROBE SHORT NEW Menu 4
		// Initial
		case strobe_short_new4:		strcpypgm2ram((char *)oled.buffer[0], strobe_short_new4_l1);
						 	 		strcpypgm2ram((char *)oled.buffer[1], strobe_short_new4_l2);
			  				 		strcpypgm2ram((char *)oled.buffer[2], strobe_short_new4_l3);
			  				 		strcpypgm2ram((char *)oled.buffer[3], strobe_short_new4_l4);
									break;

		// STROBE EXIT MENU
		// Cursor > No
		case strobe_short_exit1a:
		case strobe_long_exit1a:	strcpypgm2ram((char *)oled.buffer[0], strobe_exit_l1);
						 	 		strcpypgm2ram((char *)oled.buffer[1], strobe_exit_l2);
			  				 		strcpypgm2ram((char *)oled.buffer[2], strobe_exit_l3);
			  				 		strcpypgm2ram((char *)oled.buffer[3], strobe_exit_l4);
									oled.buffer[3][4] = oled_cursor;
									break;

		// Cursor > Yes
		case strobe_short_exit1b:
		case strobe_long_exit1b:	oled.buffer[3][4] = oled_space;	
									oled.buffer[2][4] = oled_cursor;
									break;

		// STROBE SHORT LOAD Menu 1
		// Cursor > Slot 1
		case strobe_short_load1a:	oled.buffer[0][1] = oled_cursor;
									oled.buffer[1][1] = oled_space;	
									oled.buffer[3][1] = oled_space;	
									break;

		// Cursor > Slot 2
		case strobe_short_load1b:	oled.buffer[1][1] = oled_cursor;
									oled.buffer[2][1] = oled_space;
									oled.buffer[0][1] = oled_space;								
									break;

		// Cursor > Slot 3
		case strobe_short_load1c:	oled.buffer[2][1] = oled_cursor;
									oled.buffer[1][1] = oled_space;
									oled.buffer[3][1] = oled_space;								
									break;

		// Cursor > Slot 4
		case strobe_short_load1d:	oled.buffer[3][1] = oled_cursor;
									oled.buffer[2][1] = oled_space;
									oled.buffer[0][1] = oled_space;									
									break;

		// Initial
		case strobe_short_load2: 	// Read the name in for the save selected.
									for (i = 0;	i < 14; i++) {
										name[i] = oled.buffer[stage_save_slot - 1][i + 5];
									}

									strcpypgm2ram((char *)oled.buffer[0], strobe_short_load2_l1);
				 	 				strcpypgm2ram((char *)oled.buffer[1], strobe_short_load2_l2);
	  				 				strcpypgm2ram((char *)oled.buffer[2], strobe_short_load2_l3);
	  				 				strcpypgm2ram((char *)oled.buffer[3], strobe_short_load2_l4);

									// Find out how long the name of the show playing is.
									name_length = 14;
	
									for (i = 14; i > 0; i--) {
										if (name[i-1] == ' ') {
											name_length--;
										} else {
											i = 1;
										}
									}
									
									// Centre the name on the display.
									z = 10 - (name_length * 0.5);
									ptr1 = &oled.buffer[1][z];

									// Print the name to the display on the second line.
									for (i = 0; i < name_length; i++) {
										*ptr1 = name[i];
										ptr1++;
									}

									oled.buffer[2][1] = oled_cursor;
									break;
		// Cursor >> Start
		case strobe_short_load2a_off: 	oled.buffer[2][5] = 'a';
										oled.buffer[2][6] = 'r';
										oled.buffer[2][7] = 't';
										oled.buffer[2][1] = oled_cursor;
										oled.buffer[3][1] = oled_space;
										break;
		// Cursor >> Stop
		case strobe_short_load2a_on: 	oled.buffer[2][5] = 'o';
										oled.buffer[2][6] = 'p';
										oled.buffer[2][7] = ' ';
										oled.buffer[2][1] = oled_cursor;
										oled.buffer[3][1] = oled_space;
										break;
		// Cursor >> Edit
		case strobe_short_load2b: 	oled.buffer[3][1] = oled_cursor;
									oled.buffer[2][1] = oled_space;
									break;

		// STROBE Long Menu 1
		// Cursor > New
		case strobe_long1a:	strcpypgm2ram((char *)oled.buffer[0], strobe_long1_l1);
				 	 			strcpypgm2ram((char *)oled.buffer[1], strobe_long1_l2);
	  				 			strcpypgm2ram((char *)oled.buffer[2], strobe_long1_l3);
	  				 			strcpypgm2ram((char *)oled.buffer[3], strobe_long1_l4);	
								oled.buffer[1][1] = oled_cursor;					// Point the cursor at New.			
								break;

		// Cursor > Load
		case strobe_long1b:	oled.buffer[1][1] = oled_space;	
								oled.buffer[2][1] = oled_cursor;					// Point the cursor at Load.			
								break;

		// STROBE LONG NEW Menu 1
		// Cursor > Slot 1
		case strobe_long_new1a:	oled.buffer[0][1] = oled_cursor;				// Point the cursor at Slot 1.
									oled.buffer[1][1] = oled_space;	
									oled.buffer[3][1] = oled_space;	
									break;

		// Cursor > Slot 2
		case strobe_long_new1b:	oled.buffer[1][1] = oled_cursor;				// Point the cursor at Slot 2.
									oled.buffer[2][1] = oled_space;
									oled.buffer[0][1] = oled_space;								
									break;

		// Cursor > Slot 3
		case strobe_long_new1c:	oled.buffer[2][1] = oled_cursor;				// Point the cursor at Slot 3.
									oled.buffer[1][1] = oled_space;
									oled.buffer[3][1] = oled_space;								
									break;

		// Cursor > Slot 4
		case strobe_long_new1d:	oled.buffer[3][1] = oled_cursor;				// Point the cursor at Slot 4.
									oled.buffer[2][1] = oled_space;
									oled.buffer[0][1] = oled_space;									
									break;

		// STROBE LONG NEW Menu 2
		// Initial
		case strobe_long_new2:	strcpypgm2ram((char *)oled.buffer[0], strobe_long_new2_l1);
				 	 			strcpypgm2ram((char *)oled.buffer[1], strobe_long_new2_l2);
	  				 			strcpypgm2ram((char *)oled.buffer[2], strobe_long_new2_l3);
	  				 			strcpypgm2ram((char *)oled.buffer[3], strobe_long_new2_l4);
								// Write out the stage number.

								if (stage_save_count > 99) {
									z = ((float)stage_save_count * 0.01);			// Hundreds
									oled.buffer[0][9] = z + 0x30;
									z = (((float)stage_save_count - 100.0) * 0.1);	// Tens
									oled.buffer[0][10] = z + 0x30;
									z = ((float)stage_save_count - (z * 10)) - 100;	// Ones
									oled.buffer[0][11] = z + 0x30;
								} else {
									z = ((float)stage_save_count * 0.1);		// Tens
										if (z > 0) {
											oled.buffer[0][10] = z + 0x30;
										}
									z = stage_save_count - (z * 10);
									oled.buffer[0][11] = z + 0x30;
								}		
								break;

		// Cursor > Change Colors
		case strobe_long_new2a:	oled.buffer[1][1] = oled_cursor;				
								oled.buffer[2][1] = oled_space;	
								oled.buffer[3][14] = oled_space;			
								break;

		// Cursor > Change Timing
		case strobe_long_new2b:	oled.buffer[2][1] = oled_cursor;
								oled.buffer[1][1] = oled_space;	
								oled.buffer[3][0] = oled_space;			
								break;

		// Cursor > Next
		case strobe_long_new2c:	oled.buffer[3][0] = oled_cursor;
								oled.buffer[2][1] = oled_space;	
								oled.buffer[1][0] = oled_space;	
								oled.buffer[3][7] = oled_space;		
								break;

		// Cursor > Back
		case strobe_long_new2d:	oled.buffer[3][7] = oled_cursor;
								oled.buffer[3][0] = oled_space;	
								oled.buffer[1][0] = oled_space;	
								oled.buffer[3][14] = oled_space;		
								break;

		// Cursor > Done
		case strobe_long_new2e:	oled.buffer[3][14] = oled_cursor;
								oled.buffer[3][7] = oled_space;	
								oled.buffer[1][1] = oled_space;			
								break;

		// STROBE Long New 3
		// Cursor > Zone
		case strobe_long_new3a:			oled.buffer[0][1] = oled_cursor;
										oled.buffer[1][1] = oled_space;	
										oled.buffer[3][1] = oled_space;					
										break;

		// Select > Zone
		case strobe_long_new3a_zone:	oled.buffer[0][1] = oled_space;
										break;

		// Cursor > Red
		case strobe_long_new3b:			oled.buffer[1][1] = oled_cursor;
										oled.buffer[0][1] = oled_space;
										oled.buffer[2][1] = oled_space;						
										break;

		// Select > Red
		case strobe_long_new3b_red:		oled.buffer[1][1] = oled_space;
										break;

		// Cursor > Green
		case strobe_long_new3c:			oled.buffer[2][1] = oled_cursor;
										oled.buffer[1][1] = oled_space;
										oled.buffer[3][1] = oled_space;						
										break;

		// Select > Green
		case strobe_long_new3c_green:	oled.buffer[2][1] = oled_space;
										break;

		// Cursor > Blue
		case strobe_long_new3d:			oled.buffer[3][1] = oled_cursor;
										oled.buffer[2][1] = oled_space;	
										oled.buffer[0][1] = oled_space;	
										break;

		// Select > Blue
		case strobe_long_new3d_blue:	oled.buffer[3][1] = oled_space;
										break;

		// STROBE LONG NEW Menu 4
		// Initial
		case strobe_long_new4:		strcpypgm2ram((char *)oled.buffer[0], strobe_long_new4_l1);
						 	 		strcpypgm2ram((char *)oled.buffer[1], strobe_long_new4_l2);
			  				 		strcpypgm2ram((char *)oled.buffer[2], strobe_long_new4_l3);
			  				 		strcpypgm2ram((char *)oled.buffer[3], strobe_long_new4_l4);
									break;

		// STROBE LONG LOAD Menu 1
		// Cursor > Slot 1
		case strobe_long_load1a:	oled.buffer[0][1] = oled_cursor;
									oled.buffer[1][1] = oled_space;	
									oled.buffer[3][1] = oled_space;	
									break;

		// Cursor > Slot 2
		case strobe_long_load1b:	oled.buffer[1][1] = oled_cursor;
									oled.buffer[2][1] = oled_space;
									oled.buffer[0][1] = oled_space;								
									break;

		// Cursor > Slot 3
		case strobe_long_load1c:	oled.buffer[2][1] = oled_cursor;
									oled.buffer[1][1] = oled_space;
									oled.buffer[3][1] = oled_space;								
									break;

		// Cursor > Slot 4
		case strobe_long_load1d:	oled.buffer[3][1] = oled_cursor;
									oled.buffer[2][1] = oled_space;
									oled.buffer[0][1] = oled_space;									
									break;

		// Initial
		case strobe_long_load2: 	// Read the name in for the save selected.
									for (i = 0;	i < 14; i++) {
										name[i] = oled.buffer[stage_save_slot - 5][i + 5];
									}

									strcpypgm2ram((char *)oled.buffer[0], strobe_long_load2_l1);
				 	 				strcpypgm2ram((char *)oled.buffer[1], strobe_long_load2_l2);
	  				 				strcpypgm2ram((char *)oled.buffer[2], strobe_long_load2_l3);
	  				 				strcpypgm2ram((char *)oled.buffer[3], strobe_long_load2_l4);

									// Find out how long the name of the show playing is.
									name_length = 14;
	
									for (i = 14; i > 0; i--) {
										if (name[i-1] == ' ') {
											name_length--;
										} else {
											i = 1;
										}
									}
									
									// Centre the name on the display.
									z = 10 - (name_length * 0.5);
									ptr1 = &oled.buffer[1][z];

									// Print the name to the display on the second line.
									for (i = 0; i < name_length; i++) {
										*ptr1 = name[i];
										ptr1++;
									}

									oled.buffer[2][1] = oled_cursor;
									break;
		// Cursor >> Start
		case strobe_long_load2a_off: 	oled.buffer[2][5] = 'a';
										oled.buffer[2][6] = 'r';
										oled.buffer[2][7] = 't';
										oled.buffer[2][1] = oled_cursor;
										oled.buffer[3][1] = oled_space;
										break;
		// Cursor >> Stop
		case strobe_long_load2a_on: 	oled.buffer[2][5] = 'o';
										oled.buffer[2][6] = 'p';
										oled.buffer[2][7] = ' ';
										oled.buffer[2][1] = oled_cursor;
										oled.buffer[3][1] = oled_space;
										break;
		// Cursor >> Edit
		case strobe_long_load2b: 	oled.buffer[3][1] = oled_cursor;
									oled.buffer[2][1] = oled_space;
									break;

		// Strobe Light
		case strobe_strobe1a:		strcpypgm2ram((char *)oled.buffer[0], strobe_strobe1_l1);
				 	 				strcpypgm2ram((char *)oled.buffer[1], strobe_strobe1_l2);
	  				 				strcpypgm2ram((char *)oled.buffer[2], strobe_strobe1_l3);
	  				 				strcpypgm2ram((char *)oled.buffer[3], strobe_strobe1_l4);
									break;	
	}
}

// Changes the display based on the zone being selected. 0 > All, 1 > 1, 2 > 2, etc.
void oled_load_zone(void)
{

	if (zone_select == 0) {
		print_progress_bar(1, 9, 0);
		print_progress_bar(2, 9, 0);
		print_progress_bar(3, 9, 0);
	} else {
		print_progress_bar(1, 9, zone_brightness_target[zone_select].r);
		print_progress_bar(2, 9, zone_brightness_target[zone_select].g);
		print_progress_bar(3, 9, zone_brightness_target[zone_select].b);
	}	

	switch(zone_select) {
	
		case 0:	{	oled.buffer[0][12] = 'A';
					oled.buffer[0][13] = 'l';
					oled.buffer[0][14] = 'l';
				} break;
		case 12:{	oled.buffer[0][12] = ' ';
					oled.buffer[0][13] = '1';
					oled.buffer[0][14] = '2';
				} break;
		case 11:{	oled.buffer[0][12] = ' ';
					oled.buffer[0][13] = '1';
					oled.buffer[0][14] = '1';
				} break;
		case 10: {	oled.buffer[0][12] = ' ';
					oled.buffer[0][13] = '1';
					oled.buffer[0][14] = '0';
				} break;		
		default: {	oled.buffer[0][12] = ' ';
					oled.buffer[0][13] = zone_select + 0x30;
					oled.buffer[0][14] = ' ';
				} break;
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

		Nop();
		Nop();
		sck = 1;
		Nop();
		scs = 0;				// Set Chip Select low to start transmission.
		Nop();
		Nop();
		sck = 0;				// Set clock low to get ready to clock data in.
		Nop();
		sdo = 1;				// RS = 1.
		Nop();					
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		Nop();
		sdo = 0;				// RW = 0.
		Nop();
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

		// TEST 
		strobe_lights(led_run);
		// TEST

	// OLED not ready for more data.
	oled_ready = 0;	

	// Initiate a low (800us) delay.
	TMR3H = 0xF9;
	TMR3L = 0xC0;

	// Start Timer for OLED to be ready to receive more data.
	oled_timer = 1;

}

