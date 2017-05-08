
/*****************************************************************************************
 *                                      OLED											 *
 *****************************************************************************************/

/*  Root function for processing OLED.
 *  First oled_changed is checked to see if the buffer needs different data (menu changed).
 *  Second oled_buffer is checked to see if the buffer has new data that needs to put to the
 *  display and if the display is ready for a new command it is done.
 */
void strobe_oled(void)
{
	// If menu has been changed, load the new menu into the oled buffer.
	if (oled_changed) {
		oled_load_buffer();
	}

	// If the buffer has new data and the OLED is ready for new data, send new data out.
	if (oled_buffer & oled_ready) {
		oled_send_buffer();
	}
}



/*  Processes a change to the OLED menu.
 *  This function reads the 10 bit char oled_menu and decides what is supposed to be displayed
 *  on the OLED display.  The function then loads the oled buffer with the new menu to be sent
 *  to the display in the array: oled.buffer.
 *
 */
void oled_load_buffer(void)
{
	switch (oled.menu) {
		case main_menu1:  	strcpypgm2ram(oled.buffer[0], main_menu1_l1);
			 	 			strcpypgm2ram(oled.buffer[1], main_menu1_l2);
  				 			strcpypgm2ram(oled.buffer[2], main_menu1_l3);
  				 			strcpypgm2ram(oled.buffer[3], main_menu1_l4);
				 			break;
		case select_menu1:	strcpypgm2ram(oled.buffer[0], select_menu1_l1);
			 	 			strcpypgm2ram(oled.buffer[1], select_menu1_l2);
  				 			strcpypgm2ram(oled.buffer[2], select_menu1_l3);
  				 			strcpypgm2ram(oled.buffer[3], select_menu1_l4);
							break;
		case select_menu2:	strcpypgm2ram(oled.buffer[0], select_menu2_l1);
			 	 			strcpypgm2ram(oled.buffer[1], select_menu2_l2);
  				 			strcpypgm2ram(oled.buffer[2], select_menu2_l3);
  				 			strcpypgm2ram(oled.buffer[3], select_menu2_l4);
							break;
		case select_menu3:	strcpypgm2ram(oled.buffer[0], select_menu3_l1);
			 	 			strcpypgm2ram(oled.buffer[1], select_menu3_l2);
  				 			strcpypgm2ram(oled.buffer[2], select_menu3_l3);
  				 			strcpypgm2ram(oled.buffer[3], select_menu3_l4);
							break;
		case select_menu4:	strcpypgm2ram(oled.buffer[0], select_menu4_l1);
			 	 			strcpypgm2ram(oled.buffer[1], select_menu4_l2);
  				 			strcpypgm2ram(oled.buffer[2], select_menu4_l3);
  				 			strcpypgm2ram(oled.buffer[3], select_menu4_l4);
							break;
		case select_menu5:	strcpypgm2ram(oled.buffer[0], select_menu5_l1);
			 	 			strcpypgm2ram(oled.buffer[1], select_menu5_l2);
  				 			strcpypgm2ram(oled.buffer[2], select_menu5_l3);
  				 			strcpypgm2ram(oled.buffer[3], select_menu5_l4);
							break;
		case select_menu6:	strcpypgm2ram(oled.buffer[0], select_menu6_l1);
			 	 			strcpypgm2ram(oled.buffer[1], select_menu6_l2);
  				 			strcpypgm2ram(oled.buffer[2], select_menu6_l3);
  				 			strcpypgm2ram(oled.buffer[3], select_menu6_l4);
							break;
		case motion_screen1:strcpypgm2ram(oled.buffer[0], motion_screen1_l1);
			 	 			strcpypgm2ram(oled.buffer[1], motion_screen1_l2);
  				 			strcpypgm2ram(oled.buffer[2], motion_screen1_l3);
  				 			strcpypgm2ram(oled.buffer[3], motion_screen1_l4);
							break;
		case manual_screen1:strcpypgm2ram(oled.buffer[0], manual_screen1_l1);
			 	 			strcpypgm2ram(oled.buffer[1], manual_screen1_l2);
  				 			strcpypgm2ram(oled.buffer[2], manual_screen1_l3);
  				 			strcpypgm2ram(oled.buffer[3], manual_screen1_l4);
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
		case manual_load1:	strcpypgm2ram(oled.buffer[0], manual_load1_l1);
			 	 			strcpypgm2ram(oled.buffer[1], manual_load1_l2);
  				 			strcpypgm2ram(oled.buffer[2], manual_load1_l3);
  				 			strcpypgm2ram(oled.buffer[3], manual_load1_l4);
							break;
	}
	
	// Clear the menu changed variable, buffer is now loaded.
	oled_changed = 0;

	// Set the buffer transfer variable.
	oled_buffer = 1;

	// Change the display pointer to the first location.
	oled.line = 0;
	oled.position = 0;

	// Go to the first location on the OLED display.
	while(!oled_ready);
	oled_send_command(0,0, 0x80);
			   
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
	// Complete this loop once, and repeat until new data has been printed to the OLED (!oled_ready).
	do {
	
		// Print the new data to the display, change oled.display to show it has the new data.
		oled_print(oled.buffer[oled.line][oled.position]);
		oled.display[oled.line][oled.position] = oled.buffer[oled.line][oled.position];
	
		// If the pointer is in the last position, clear oled_buffer, all of the buffer data has been sent.
		if (oled.line == 3 && oled.position == 19) {
			oled_buffer = 0;
			return;
		} else {

			// If the pointer is at the end of a line, move to the start of the next line.
			if (oled.position == 19) {
				oled.line++;
				oled.position = 0;
				while(!oled_ready);
				
				// Move the cursor to the start of the appropriate line.
				switch (oled.line) {
					case 1:	oled_send_command(0, 0, 0xC0);
							break;
					case 2: oled_send_command(0, 0, 0x94);
							break;
					case 3: oled_send_command(0, 0, 0xD4);
							break;
				}

			// If the point is not at the end of the line, just increase the position on the same line.			
			} else {
				oled.position++;
			}
		}
	} while (oled_ready);

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
	unsigned char lowh = 0xFB;
	unsigned char lowl = 0x50;

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
	sck = 1;
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b6;
	Nop();
	sck = 1;
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b5;
	Nop();
	sck = 1;
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b4;
	Nop();
	sck = 1;
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b3;
	Nop();
	sck = 1;
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b2;
	Nop();
	sck = 1;
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b1;
	Nop();
	sck = 1;
	Nop();
	Nop();
	Nop();
	sck = 0;
	sdo = oled_command.b0;
	Nop();
	sck = 1;
	Nop();
	scs = 1;

	// OLED not ready for more data.
	oled_ready = 0;	

	// If the command is a reset, initiate a high (2ms) delay.
	// Otherwise intiate a low (600us) delay.
	if (oled_command.byte == 0x01) {
		oled_timer_delayh = highh;
		oled_timer_delayl = highl;
	} else {
		oled_timer_delayh = lowh;
		oled_timer_delayl = lowl;
	}

	// Start Timer for OLED to be ready to receive more data.
	oled_timer = 1;
}


/*  Print a character to the OLED Display.
 *  This function passes an unsigned char into the array which is then printed to the OLED
 *  display.  The function prints: RS, RW, B7, B6, B5, B4, B3, B2, B1, B0.
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
		sdo = 1;				// Send RS out the data line.
		Nop();					
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = 0;				// Send RW out the data line.
		Nop();
		sck = 1;				// Clock in the data.
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b7;
		Nop();
		sck = 1;
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b6;
		Nop();
		sck = 1;
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b5;
		Nop();
		sck = 1;
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b4;
		Nop();
		sck = 1;
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b3;
		Nop();
		sck = 1;
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b2;
		Nop();
		sck = 1;
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b1;
		Nop();
		sck = 1;
		Nop();
		Nop();
		Nop();
		sck = 0;
		sdo = oled_data.b0;
		Nop();
		sck = 1;
		Nop();
		scs = 1;

	// OLED not ready for more data.
	oled_ready = 0;	

	// Initiate a low (600us) delay.
	oled_timer_delayh = 0xFB;
	oled_timer_delayl = 0x50;

	// Start Timer for OLED to be ready to receive more data.
	oled_timer = 1;
}

