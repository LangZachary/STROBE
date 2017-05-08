
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
	// 2 - Load the oled buffer with new motion sensor adc data.
	// 3 - Load the oled buffer with the selected zone being changed in manual mode.
	// 4 - Load the oled buffer with color changes in manual mode.
	// 5 - General operation.
	switch (oled_process) {

		// Load buffer with new menu data.
		case oled_menu:	{

							oled_load_menu();			
			
						} break;

		// Load buffer with new selected zone in manual mode.
		case oled_manual_zone: {

							oled_load_manual_zone();

						} break;

		// Load buffer with new color change in manual mode.
		case oled_manual_color: {

							

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

	static unsigned char select = 0;

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

		// Manual Menu 1
		case manual_menu1:		strcpypgm2ram(oled.buffer[0], manual_menu1_l1);
			 	 				strcpypgm2ram(oled.buffer[1], manual_menu1_l2);
  				 				strcpypgm2ram(oled.buffer[2], manual_menu1_l3);
  				 				strcpypgm2ram(oled.buffer[3], manual_menu1_l4);
								oled.buffer[0][1] = oled_cursor;					// Point the cursor at Zone.
								break;

		// Cursor > Zone
		case manual_menu1a:		oled.buffer[0][1] = oled_cursor;					// Point the cursor at Zone.
								oled.buffer[1][1] = oled_space;					
								break;

		// Select > Zone
		case manual_menu1a_zone:oled.buffer[0][1] = oled_space;
								select = 1;
								break;

		// Cursor > Red
		case manual_menu1b:		oled.buffer[1][1] = oled_cursor;					// Point the cursor at Red.
								oled.buffer[0][1] = oled_space;
								oled.buffer[2][1] = oled_space;						
								break;

		// Select > Red
		case manual_menu1b_red:	oled.buffer[1][1] = oled_space;
								break;

		// Cursor > Green
		case manual_menu1c:		if (select) {
									oled.buffer[2][1] = oled_cursor;					// Point the cursor at Green.
									select = 0;
								} else {
									oled.buffer[2][1] = oled_cursor;					// Point the cursor at Green.
									oled.buffer[1][1] = oled_space;
									oled.buffer[3][1] = oled_space;	
								}					
								break;

		// Select > Green
		case manual_menu1c_green:oled.buffer[2][1] = oled_space;
								select = 1;
								break;

		// Cursor > Blue
		case manual_menu1d:		if (select) {
									oled.buffer[3][1] = oled_cursor;					// Point the cursor at Blue.
									select = 0;
								} else {
									oled.buffer[3][1] = oled_cursor;					// Point the cursor at Blue.
									oled.buffer[2][1] = oled_space;	
								}					
								break;

		// Select > Blue
		case manual_menu1d_blue:oled.buffer[3][1] = oled_space;
								select = 1;
								break;

	}
	
	return;			   
}

// Changes the display based on the zone being selected. 0 > All, 1 > 1, 2 > 2, etc.
void oled_load_manual_zone(void)
{
	switch(manual_zone_select) {
	
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
					oled.buffer[0][13] = manual_zone_select + 0x30;
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

	// OLED not ready for more data.
	oled_ready = 0;	

	// Initiate a low (800us) delay.
	TMR3H = 0xF9;
	TMR3L = 0xC0;

	// Start Timer for OLED to be ready to receive more data.
	oled_timer = 1;

	INTCONbits.GIE = 1;			// Enable all interrupts after data is sent to OLED.

}

