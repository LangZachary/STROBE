/*************************************************************************************
 *                                  Memory											 *
 *************************************************************************************/

/*  Root function for processing Program Memory saves and loads.
 */
void strobe_mem(unsigned char mem_process, unsigned char slot, static unsigned char *trigger)
{

	static unsigned long	save_mem_add_start = 0;
	static unsigned long	save_mem_add_current = 0;

	unsigned char			*name_ptr;
	unsigned char			i;


	// Variable passed into the function decides which process is completed.
	switch (mem_process) {

		case mem_save_init:	{	// Save the current name that is in the OLED buffer.
										name_ptr = &oled.buffer[slot - 1][5];
			
										for (i = 0; i < 14; i++) {
											name[i] = *name_ptr;
											name_ptr++;
										}

										// Initialize blinking of the letters so the user knows which one they are changing.
										strobe_blink(blink_init);

										current_letter = 0;			// Point to the first character for change.

										} break;


		case mem_save_run:	{	switch (*trigger) {

											// UP PRESSED //
											case button_up_pressed:	{	if (name[current_letter] == 0x41) { // A >> Done
																			name[current_letter] = 0xFF;
																		} else if (name[current_letter] == 0xFF) { // Done >> _
																			name[current_letter] = 0x20;
																		} else if (name[current_letter] == 0x20) { // _ >> 9
																			name[current_letter] = 0x39;	
																		} else if (name[current_letter] == 0x30) { // 0 >> z
																			name[current_letter] = 0x7A;
																		} else if (name[current_letter] == 0x61) { // a >> Z
																			name[current_letter] = 0x5A;
																		} else {
																			name[current_letter]--;
																		}
																		blink(1);
																	} break;	

											// DOWN PRESSED //
											case button_down_pressed:{	if (name[current_letter] == 0xFF) { // A >> Done
																			name[current_letter] = 0x41;
																		} else if (name[current_letter] == 0x20) { // Done >> _
																			name[current_letter] = 0xFF;
																		} else if (name[current_letter] == 0x39) { // _ >> 9
																			name[current_letter] = 0x20;	
																		} else if (name[current_letter] == 0x7A) { // 0 >> z
																			name[current_letter] = 0x30;
																		} else if (name[current_letter] == 0x5A) { // a >> Z
																			name[current_letter] = 0x61;
																		} else {
																			name[current_letter]++;
																		}
																		blink(1);
																	} break;
								
											// ENTER PRESSED //
											case button_enter_pressed:{	// When a block is entered, or on last letter, the user is finished entering the name.
																		if ((name[current_letter] == 0xFF) || (current_letter == 13)) {
																			
																			// Fill remaining spaces with spaces.
																			if (current_letter < 13) {
																				
																				for (i = current_letter; i <= 13; i++) {
																					name[i] = ' ';
																				}
																			}			
																			strobe_blink(blink_deinit);

																			switch (oled.menu) {

																				case	manual_save_name1:
																				case	manual_save_name2:
																				case	manual_save_name3:
																				case	manual_save_name4:	oled.menu = manual_menu1a;
																											strobe_oled(oled_menu, 0, 0);
																											mem_manual_save(slot);
																											strobe_lights(led_deinit);
																											break;
																		
																				case	strobe_short_save_name:	oled.menu = strobe_short1a;
																												strobe_oled(oled_menu, 0, 0);
																												lights_stage(stage_deinit, 0);
																												break;

																				case	strobe_long_save_name:	oled.menu = strobe_long1a;
																												strobe_oled(oled_menu, 0, 0);
																												lights_stage(stage_deinit, 0);
																												break;
																			}
																		} else {
																			blink(1);				// Force the current item to reappear.
																			current_letter++;		// Point to the next letter.
																		} 
																	} break;


										} 	
									} break;

		case mem_manual_load_names: {	// Get name 1 from memory.
										mem_print_name(manual1_name_add, 0);
	
										// Get name 2 from memory.
										mem_print_name(manual2_name_add, 1);

										// Get name 3 from memory.
										mem_print_name(manual3_name_add, 2);

										// Get name 4 from memory.
										mem_print_name(manual4_name_add, 3);

									} break;

		case mem_strobe_short_load_names: {	// Get name 1 from memory.
											mem_print_name(strobe_short1_name_add, 0);
	
											// Get name 2 from memory.
											mem_print_name(strobe_short2_name_add, 1);

											// Get name 3 from memory.
											mem_print_name(strobe_short3_name_add, 2);

											// Get name 4 from memory.
											mem_print_name(strobe_short4_name_add, 3);

									} break;

		case mem_strobe_long_load_names: {	// Get name 1 from memory.
											mem_print_name(strobe_long1_name_add, 0);
	
											// Get name 2 from memory.
											mem_print_name(strobe_long2_name_add, 1);

											// Get name 3 from memory.
											mem_print_name(strobe_long3_name_add, 2);

											// Get name 4 from memory.
											mem_print_name(strobe_long4_name_add, 3);

									} break;							
	}	
}															

/*	Manual Lights Save Command.
 *	This function saves light settings to one of the four manual locations.
 *  slot -		The save location that the settings are to be loaded from. (1 - 4).
 */
void mem_manual_save(unsigned char slot)
{
	unsigned char i;

	// Test for Ready Step.
	while (EECON1bits.WR);
	while (EECON1bits.RD);

	// Point to the correct memory location for the manual saves.
	switch (slot) {

		case 1: {
					TBLPTR = manual1_config_add;
				} break;

		case 2: {
					TBLPTR = manual2_config_add;		
				} break;

		case 3: {
					TBLPTR = manual3_config_add;		
				} break;

		case 4: {
					TBLPTR = manual4_config_add;		
				} break;
	}

	// Store Config in Table.
	TABLAT = config[0];			// Store the config bytes.
    _asm TBLWTPOSTINC _endasm   // Table write.
	TABLAT = config[1];
    _asm TBLWTPOSTINC _endasm   // Table write.

	// Store Name in Table.
	for (i = 0; i < 14; i++) {	// Store the name bytes.

		if (name[i] == 0xFF) {	// If the character is a block,
			TABLAT = ' ';		// replace with a space.
		} else {
			TABLAT = name[i];
		}

   		_asm TBLWTPOSTINC _endasm   // Table write.
	}

	// Store Red brightness in Table.
	for (i = 1; i <= 12; i++) {	// Store the Red zone brightnesses.

		TABLAT = zone_brightness_target[i].r;
		_asm TBLWTPOSTINC _endasm   // Table write.				
	}
	
	// Fill in the 4 Bytes in the 16 Byte block.
	TABLAT = 0;
   	_asm TBLWTPOSTINC _endasm   // Table write.
	TABLAT = 0;
   	_asm TBLWTPOSTINC _endasm   // Table write.
	TABLAT = 0;
   	_asm TBLWTPOSTINC _endasm   // Table write.
	TABLAT = 0;
   	_asm TBLWTPOSTINC _endasm   // Table write.

	// Store Green brightness in Table.
	for (i = 1; i <= 12; i++) {	// Store the Red zone brightnesses.

		TABLAT = zone_brightness_target[i].g;
		_asm TBLWTPOSTINC _endasm   // Table write.				
	}
	
	// Fill in the 4 Bytes in the 16 Byte block.
	TABLAT = 0;
   	_asm TBLWTPOSTINC _endasm   // Table write.
	TABLAT = 0;
   	_asm TBLWTPOSTINC _endasm   // Table write.
	TABLAT = 0;
   	_asm TBLWTPOSTINC _endasm   // Table write.
	TABLAT = 0;
   	_asm TBLWTPOSTINC _endasm   // Table write.

	// Store Blue brightness in Table.
	for (i = 1; i <= 12; i++) {	// Store the Red zone brightnesses.

		TABLAT = zone_brightness_target[i].b;
		_asm TBLWTPOSTINC _endasm   // Table write.				
	}

	mem_write_cmd();		// Write the data to flash memory.

}
/*	Print Name from memory command.
 *	This function reads the name from the location at mem_location. The function will then
 *  print it out to the line of the display defined by the variable line.  The name will be printed
 *  started at the 5th location of the display. 14 characters total will be read.
 *  mem_location - 	Memory location that the name to be printed is starting at.
 *  line -			Line number that the name will be printed on started from fifth character over.
 */
void mem_print_name(unsigned long mem_location, unsigned char line)
{
	unsigned char	*name_ptr;
	unsigned char	i;

	name_ptr = &name[0];
	mem_read(mem_location, name_ptr, 14);

	if (name[0] == 0xFF) {			// If the first character is a block
		name[0] = 'E';				// the location is empty so enter Empty
		name[1] = 'm';				// for the name.
		name[2] = 'p';	
		name[3] = 't';
		name[4] = 'y';
		name[5] = ' ';
		name[6] = ' ';
		name[7] = ' ';
		name[8] = ' ';
		name[9] = ' ';
		name[10] = ' ';
		name[11] = ' ';
		name[12] = ' ';
		name[13] = ' ';
	}

	for (i = 0; i < 14; i++) {

		oled.buffer[line][i + 5] = name[i];

	}
}

/*	Manual Lights Read Command.
 *	This function reads saved light settings from the flash memory. The light settings
 *	can be loaded from any of the slots 1 to 4.
 *  slot -		The save location that the settings are to be loaded from. (1 - 4).
 */
void mem_manual_load_lights(unsigned char slot)
{
	unsigned char i;
	unsigned char red[13];
	unsigned char green[13];
	unsigned char blue[13];

	// Test for Ready Step.
	while (EECON1bits.WR);
	while (EECON1bits.RD);

	switch (slot) {

		case 1: {
					mem_read(manual1_red_add, &red[1], 12);
					mem_read(manual1_green_add, &green[1], 12);
					mem_read(manual1_blue_add, &blue[1], 12);
				} break;

		case 2: {
					mem_read(manual2_red_add, &red[1], 12);
					mem_read(manual2_green_add, &green[1], 12);
					mem_read(manual2_blue_add, &blue[1], 12);		
				} break;

		case 3: {
					mem_read(manual3_red_add, &red[1], 12);
					mem_read(manual3_green_add, &green[1], 12);
					mem_read(manual3_blue_add, &blue[1], 12);		
				} break;

		case 4: {
					mem_read(manual4_red_add, &red[1], 12);
					mem_read(manual4_green_add, &green[1], 12);
					mem_read(manual4_blue_add, &blue[1], 12);		
				} break;
	}

	// Activate the saved light settings.
	for (i = 1; i <= 12; i++) {

		zone_brightness_target[i].r = red[i];
		zone_brightness_target[i].g = green[i];
		zone_brightness_target[i].b = blue[i];

	}
}


/*	Memory Read Command.
 *	This function will read a string of values from the flash memory.
 *  mem_add_start -		Start address for the flash memory to be read.
 *	*data -				Pointer to string save location.
 *	length -			Number of characters to read from the flash memory.
 */
void mem_read(unsigned long mem_add_start, unsigned char *data, unsigned char length)
{
	unsigned char i;

	TBLPTR = mem_add_start;

	for (i = 1; i <= length; i++) {
		_asm TBLRDPOSTINC _endasm   // Table read.
		*data = TABLAT;				// Read the config bytes.
		data++;
	}
}

/*	Memory Write Command.
 *	This function will write a string of values to the flash memory.
 *  mem_add_start -		Start address for the flash memory to be written.
 *	*data -				Pointer to string save location.
 *	length -			Number of characters to read from the flash memory.
 */
void mem_write(unsigned long mem_add_start, unsigned char *data, unsigned char length)
{
	unsigned char i;

	TBLPTR = mem_add_start;

	for (i = 1; i <= length; i++) {
		TABLAT = *data;
 	   _asm TBLWTPOSTINC _endasm   // Table write.
		data++;
	}

	mem_write_cmd();

}


/*	Memory Write Command.
 *	This function will send the data in the flash program memory table into
 *  the flash memory location already pointed to by TBLPTR.
 */
void mem_write_cmd(void)
{
	EECON1bits.EEPGD = 1;		// Point to flash memory.
	EECON1bits.CFGS = 0;

	EECON1bits.WREN = 1;		// Enable write operations.
	
	INTCONbits.GIE = 0;			// Disable interrupts for the write sequence.

	EECON2 = 0x55;				// Special write sequence.
	EECON2 = 0xAA;

	EECON1bits.WR = 1;			// Initiate the write.

	// CPU IDLE //

	INTCONbits.GIE = 1;			// Enable interrupts after write sequence.

	EECON1bits.WREN = 0;		// Disable write operations.
}

/*	Memory Erase Command.
 *	This function will erase the flash memory starting from the start address until the
 *	end address. Flash memory is erased in 128 byte blocks. The erase command will continue to
 *  erase 128 byte blocks of flash memory until the address at mem_add_stop is erased.
 *  mem_add_start -		Start address for the flash memory to be erased.
 *	mem_add_end	-		Stop address for the flash memory to be erased.
 */
void mem_erase(unsigned long mem_add_start, unsigned long mem_add_stop)
{
	
	unsigned char done;

	do {

		// Test for Ready Step.
		while (EECON1bits.WR);
		while (EECON1bits.RD);

		// Erase Step.
		TBLPTR = mem_add_start;
	
		EECON1bits.EEPGD = 1;		// Point to Flash Memory.
		EECON1bits.CFGS = 0;
		EECON1bits.WREN = 1;		// Enable write operations.
		EECON1bits.FREE = 1;		// Enable erase operation.

		done = 1;					// Initialize repetition bit.
	
		INTCONbits.GIE = 0;			// Disable interrupts.
	
		EECON2 = 0x55;				// Execution Command.
		EECON2 = 0xAA;
	
		EECON1bits.WR = 1;			// Start Erase.
	
		// CPU IDLE //
	
		EECON1bits.FREE = 0;		// Disable erase operation.
		EECON1bits.WREN = 0;		// Disable write operations.

		INTCONbits.GIE = 1;			// Enable interrupts.


	
		if ((mem_add_start + 0x80) < mem_add_stop) {
	
			mem_add_start = mem_add_start + 0x80;				// Erase the next block.
	
			done = 0;				// Repeat the erase cycle.
		}

	}while (!done);
}

