

// This function prints a progress bar out to the OLED display. 
// row - 			The row of the display the progress bar will be printed on. 0 for top, 3 for bottom.
// start_position - The spot on the row the progress bar will start on. This position must be ten or more
//					characters from the right edge for the function to work correctly.
// percent -		How full the progress bar is. This number must be from 0 - 100 to display correctly.
void print_progress_bar(unsigned char row, unsigned char start_position, unsigned char percent)
{
	unsigned char i;	


	strobe_lights(led_run);				// Check the lights.

	switch (percent) {
		
			case 0:		for (i = 0; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 1:
			case 2:		oled.buffer[row][start_position] = oled_load1;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 3:
			case 4:		oled.buffer[row][start_position] = oled_load2;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 5:
			case 6:		oled.buffer[row][start_position] = oled_load3;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 7:
			case 8:		oled.buffer[row][start_position] = oled_load4;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 9:
			case 10:	oled.buffer[row][start_position] = oled_load5;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 11:
			case 12:	for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load1;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 13:
			case 14:	for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load2;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 15:
			case 16:	for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load3;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 17:
			case 18:	for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load4;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 19:
			case 20:	for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load5;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;
	}

		strobe_lights(led_run);						// Check the lights.

		switch (percent) {

			case 21:
			case 22:	for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load1;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 23:
			case 24:	for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load2;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 25:
			case 26:	for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load3;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 27:
			case 28:	for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load4;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 29:
			case 30:	for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load5;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 31:
			case 32:	for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load1;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 33:
			case 34:	for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load2;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 35:
			case 36:	for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load3;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 37:
			case 38:	for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load4;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 39:
			case 40:	for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load5;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

		}

		strobe_lights(led_run);						// Check the lights.

		switch (percent) {

			case 41:
			case 42:	for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load1;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 43:
			case 44:	for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load2;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 45:
			case 46:	for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load3;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 47:
			case 48:	for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load4;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 49:
			case 50:	for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load5;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 51:
			case 52:	for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load1;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 53:
			case 54:	for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load2;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 55:
			case 56:	for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load3;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 57:
			case 58:	for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load4;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 59:
			case 60:	for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load5;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

	}

	strobe_lights(led_run);						// Check the lights.

	switch (percent) {

			case 61:
			case 62:	for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load1;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 63:
			case 64:	for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load2;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 65:
			case 66:	for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load3;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 67:
			case 68:	for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load4;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 69:
			case 70:	for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load5;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 71:
			case 72:	for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load1;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 73:
			case 74:	for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load2;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 75:
			case 76:	for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load3;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 77:
			case 78:	for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load4;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 79:
			case 80:	for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load5;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

	}

	strobe_lights(led_run);						// Check the lights.

	switch (percent) {

			case 81:
			case 82:	for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load1;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 83:
			case 84:	for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load2;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 85:
			case 86:	for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load3;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 87:
			case 88:	for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load4;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 89:
			case 90:	for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load5;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 91:
			case 92:	for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load1;
						break;

			case 93:
			case 94:	for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load2;
						break;

			case 95:
			case 96:	for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load3;
						break;

			case 97:
			case 98:	for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load4;
						break;

			case 99:
			case 100:	for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load5;
						break;
		}

		strobe_lights(led_run);						// Check the lights.

}

// This function prints the Timeout Delay for Motion Sensing mode in the Options.
// The length of the time out delay is printed in the top right corner of the OLED and the progress
// bar is printed in the centre of the second line down.
void print_delay(unsigned char percent, unsigned char delay_process)
{

	unsigned char i;
	unsigned int z;

	switch (percent) {
		
			case 0:		z = 0;							// 0s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';
						break;
			case 1:
			case 2:		z = 1;							// 0.1s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '1';
						oled.buffer[0][19] = 's';
						break;
			case 3:
			case 4:		z = 2;							// 0.2s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '2';
						oled.buffer[0][19] = 's';
						break;
			case 5:
			case 6:		z = 3;							// 0.3s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '3';
						oled.buffer[0][19] = 's';
						break;
			case 7:
			case 8:		z = 4;							// 0.4s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '4';
						oled.buffer[0][19] = 's';
						break;
			case 9:
			case 10:	z = 5;							// 0.5s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 's';
						break;
			case 11:
			case 12:	z = 6;							// 0.6s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '6';
						oled.buffer[0][19] = 's';
						break;
			case 13:
			case 14:	z = 7;							// 0.7s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '7';
						oled.buffer[0][19] = 's';
						break;
			case 15:
			case 16:	z = 8;							// 0.8s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '8';
						oled.buffer[0][19] = 's';
						break;
			case 17:
			case 18:	z = 9;							// 0.9s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '9';
						oled.buffer[0][19] = 's';
						break;
			case 19:
			case 20:	z = 10;						// 1s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '1';
						oled.buffer[0][19] = 's';
						break;
			case 21:
			case 22:	z = 20;						// 2s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '2';
						oled.buffer[0][19] = 's';
						break;
			case 23:
			case 24:	z = 30;						// 3s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '3';
						oled.buffer[0][19] = 's';
						break;
			case 25:
			case 26:	z = 40;						// 4s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '4';
						oled.buffer[0][19] = 's';
						break;
			case 27:
			case 28:	z = 50;						// 5s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 's';
						break;
			case 29:
			case 30:	z = 60;						// 6s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '6';
						oled.buffer[0][19] = 's';
						break;
			case 31:
			case 32:	z = 70;						// 7s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '7';
						oled.buffer[0][19] = 's';
						break;
			case 33:
			case 34:	z = 80;						// 8s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '8';
						oled.buffer[0][19] = 's';
						break;
			case 35:
			case 36:	z = 90;						// 9s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '9';
						oled.buffer[0][19] = 's';
						break;
			case 37:
			case 38:	z = 100;						// 10s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';
						break;
			case 39:
			case 40:	z = 120;						// 12s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '2';
						oled.buffer[0][19] = 's';
						break;
			case 41:
			case 42:	z = 140;						// 14s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '4';
						oled.buffer[0][19] = 's';
						break;
			case 43:
			case 44:	z = 160;						// 16s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '6';
						oled.buffer[0][19] = 's';
						break;
			case 45:
			case 46:	z = 180;						// 18s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '8';
						oled.buffer[0][19] = 's';
						break;
			case 47:
			case 48:	z = 200;						// 20s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';
						break;
			case 49:
			case 50:	z = 220;						// 22s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '2';
						oled.buffer[0][19] = 's';
						break;
			case 51:
			case 52:	z = 240;						// 24s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '4';
						oled.buffer[0][19] = 's';
						break;
			case 53:
			case 54:	z = 260;						// 26s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '6';
						oled.buffer[0][19] = 's';
						break;
			case 55:
			case 56:	z = 280;						// 28s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '8';
						oled.buffer[0][19] = 's';
						break;
			case 57:
			case 58:	z = 300;						// 30s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '3';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';
						break;
			case 59:
			case 60:	z = 350;						// 35s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '3';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 's';
						break;
			case 61:
			case 62:	z = 400;						// 40s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '4';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';
						break;
			case 63:
			case 64:	z = 450;						// 45s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '4';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 's';
						break;
			case 65:
			case 66:	z = 500;						// 50s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '5';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';
						break;
			case 67:
			case 68:	z = 550;						// 55s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '5';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 's';
						break;
			case 69:
			case 70:	z = 600;						// 1m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '1';
						oled.buffer[0][19] = 'm';
						break;
			case 71:
			case 72:	z = 1200;						// 2m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '2';
						oled.buffer[0][19] = 'm';
						break;
			case 73:
			case 74:	z = 1800;						// 3m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '3';
						oled.buffer[0][19] = 'm';
						break;
			case 75:
			case 76:	z = 2400;						// 4m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '4';
						oled.buffer[0][19] = 'm';
						break;
			case 77:
			case 78:	z = 3000;						// 5m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 'm';
						break;
			case 79:
			case 80:	z = 3600;						// 6m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '6';
						oled.buffer[0][19] = 'm';
						break;
			case 81:
			case 82:	z = 4200;						// 7m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '7';
						oled.buffer[0][19] = 'm';
						break;
			case 83:
			case 84:	z = 4800;						// 8m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '8';
						oled.buffer[0][19] = 'm';
						break;
			case 85:
			case 86:	z = 5400;						// 9m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '9';
						oled.buffer[0][19] = 'm';
						break;
			case 87:
			case 88:	z = 6000;						// 10m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 'm';
						break;
			case 89:
			case 90:	z = 9000;						// 15m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 'm';
						break;
			case 91:
			case 92:	z = 12000;						// 20m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 'm';
						break;
			case 93:
			case 94:	z = 15000;						// 25m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 'm';
						break;
			case 95:
			case 96:	z = 18000;						// 30m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '3';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 'm';
						break;
			case 97:
			case 98:	z = 27000;						// 45m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '4';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 'm';
						break;
			case 99:
			case 100:	z = 36000;						// 1hr
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = 'h';
						oled.buffer[0][19] = 'r';
						break;
		}

		switch (delay_process) {

			case timeout_delay:	print_progress_bar(1, 5, percent);	// Print a progress bar.
								zone_timeout_delay = ++z;			// The timeout function uses 0 as meaning not active and delay being 1-36000.
								break;
			case hold_time:		print_progress_bar(1, 5, percent);	// Print a progress bar.
								adc_hold_time = (z * 25);
								if (adc_hold_time == 0) {
									adc_hold_time = 1;
								}
								break;
		}
						
}

// This function prints the Light Spread for the Motion Sensing mode in the Options menu.
// The progress bar for the Light Spread should be printed in the center of the bottom line of the OLED.
void print_ms_lightspread(unsigned char percent)
{
	unsigned char i;	


	switch (percent) {
		
			case 0:		adjacent_brightness	= ab_step1;
						adjacent2_brightness = a2b_step1;
						adjacent3_brightness = a3b_step1;
						break;
			case 1:
			case 2:		adjacent_brightness	= ab_step2;
						adjacent2_brightness = a2b_step2;
						adjacent3_brightness = a3b_step2;
						break;
			case 3:
			case 4:		adjacent_brightness	= ab_step3;
						adjacent2_brightness = a2b_step3;
						adjacent3_brightness = a3b_step3;
						break;
			case 5:
			case 6:		adjacent_brightness	= ab_step4;
						adjacent2_brightness = a2b_step4;
						adjacent3_brightness = a3b_step4;
						break;
			case 7:
			case 8:		adjacent_brightness	= ab_step5;
						adjacent2_brightness = a2b_step5;
						adjacent3_brightness = a3b_step5;
						break;
			case 9:
			case 10:	adjacent_brightness	= ab_step6;
						adjacent2_brightness = a2b_step6;
						adjacent3_brightness = a3b_step6;
						break;
			case 11:
			case 12:	adjacent_brightness	= ab_step7;
						adjacent2_brightness = a2b_step7;
						adjacent3_brightness = a3b_step7;
						break;
			case 13:
			case 14:	adjacent_brightness	= ab_step8;
						adjacent2_brightness = a2b_step8;
						adjacent3_brightness = a3b_step8;
						break;
			case 15:
			case 16:	adjacent_brightness	= ab_step9;
						adjacent2_brightness = a2b_step9;
						adjacent3_brightness = a3b_step9;
						break;
			case 17:
			case 18:	adjacent_brightness	= ab_step10;
						adjacent2_brightness = a2b_step10;
						adjacent3_brightness = a3b_step10;
						break;
			case 19:
			case 20:	adjacent_brightness	= ab_step11;
						adjacent2_brightness = a2b_step11;
						adjacent3_brightness = a3b_step11;
						break;
			case 21:
			case 22:	adjacent_brightness	= ab_step12;
						adjacent2_brightness = a2b_step12;
						adjacent3_brightness = a3b_step12;
						break;
			case 23:
			case 24:	adjacent_brightness	= ab_step13;
						adjacent2_brightness = a2b_step13;
						adjacent3_brightness = a3b_step13;
						break;
			case 25:
			case 26:	adjacent_brightness	= ab_step14;
						adjacent2_brightness = a2b_step14;
						adjacent3_brightness = a3b_step14;
						break;
			case 27:
			case 28:	adjacent_brightness	= ab_step15;
						adjacent2_brightness = a2b_step15;
						adjacent3_brightness = a3b_step15;
						break;
			case 29:
			case 30:	adjacent_brightness	= ab_step16;
						adjacent2_brightness = a2b_step16;
						adjacent3_brightness = a3b_step16;
						break;
			case 31:
			case 32:	adjacent_brightness	= ab_step17;
						adjacent2_brightness = a2b_step17;
						adjacent3_brightness = a3b_step17;
						break;
			case 33:
			case 34:	adjacent_brightness	= ab_step18;
						adjacent2_brightness = a2b_step18;
						adjacent3_brightness = a3b_step18;
						break;
			case 35:
			case 36:	adjacent_brightness	= ab_step19;
						adjacent2_brightness = a2b_step19;
						adjacent3_brightness = a3b_step19;
						break;
			case 37:
			case 38:	adjacent_brightness	= ab_step20;
						adjacent2_brightness = a2b_step20;
						adjacent3_brightness = a3b_step20;
						break;
			case 39:
			case 40:	adjacent_brightness	= ab_step21;
						adjacent2_brightness = a2b_step21;
						adjacent3_brightness = a3b_step21;
						break;
			case 41:
			case 42:	adjacent_brightness	= ab_step22;
						adjacent2_brightness = a2b_step22;
						adjacent3_brightness = a3b_step22;
						break;
			case 43:
			case 44:	adjacent_brightness	= ab_step23;
						adjacent2_brightness = a2b_step23;
						adjacent3_brightness = a3b_step23;
						break;
			case 45:
			case 46:	adjacent_brightness	= ab_step24;
						adjacent2_brightness = a2b_step24;
						adjacent3_brightness = a3b_step24;
						break;
			case 47:
			case 48:	adjacent_brightness	= ab_step25;
						adjacent2_brightness = a2b_step25;
						adjacent3_brightness = a3b_step25;
						break;
			case 49:
			case 50:	adjacent_brightness	= ab_step26;
						adjacent2_brightness = a2b_step26;
						adjacent3_brightness = a3b_step26;
						break;
			case 51:
			case 52:	adjacent_brightness	= ab_step27;
						adjacent2_brightness = a2b_step27;
						adjacent3_brightness = a3b_step27;
						break;
			case 53:
			case 54:	adjacent_brightness	= ab_step28;
						adjacent2_brightness = a2b_step28;
						adjacent3_brightness = a3b_step28;
						break;
			case 55:
			case 56:	adjacent_brightness	= ab_step29;
						adjacent2_brightness = a2b_step29;
						adjacent3_brightness = a3b_step29;
						break;
			case 57:
			case 58:	adjacent_brightness	= ab_step30;
						adjacent2_brightness = a2b_step30;
						adjacent3_brightness = a3b_step30;
						break;
			case 59:
			case 60:	adjacent_brightness	= ab_step31;
						adjacent2_brightness = a2b_step31;
						adjacent3_brightness = a3b_step31;
						break;
			case 61:
			case 62:	adjacent_brightness	= ab_step32;
						adjacent2_brightness = a2b_step32;
						adjacent3_brightness = a3b_step32;
						break;
			case 63:
			case 64:	adjacent_brightness	= ab_step33;
						adjacent2_brightness = a2b_step33;
						adjacent3_brightness = a3b_step33;
						break;
			case 65:
			case 66:	adjacent_brightness	= ab_step34;
						adjacent2_brightness = a2b_step34;
						adjacent3_brightness = a3b_step34;
						break;
			case 67:
			case 68:	adjacent_brightness	= ab_step35;
						adjacent2_brightness = a2b_step35;
						adjacent3_brightness = a3b_step35;
						break;
			case 69:
			case 70:	adjacent_brightness	= ab_step36;
						adjacent2_brightness = a2b_step36;
						adjacent3_brightness = a3b_step36;
						break;
			case 71:
			case 72:	adjacent_brightness	= ab_step37;
						adjacent2_brightness = a2b_step37;
						adjacent3_brightness = a3b_step37;
						break;
			case 73:
			case 74:	adjacent_brightness	= ab_step38;
						adjacent2_brightness = a2b_step38;
						adjacent3_brightness = a3b_step38;
						break;
			case 75:
			case 76:	adjacent_brightness	= ab_step39;
						adjacent2_brightness = a2b_step39;
						adjacent3_brightness = a3b_step39;
						break;
			case 77:
			case 78:	adjacent_brightness	= ab_step40;
						adjacent2_brightness = a2b_step40;
						adjacent3_brightness = a3b_step40;
						break;
			case 79:
			case 80:	adjacent_brightness	= ab_step41;
						adjacent2_brightness = a2b_step41;
						adjacent3_brightness = a3b_step41;
						break;
			case 81:
			case 82:	adjacent_brightness	= ab_step42;
						adjacent2_brightness = a2b_step42;
						adjacent3_brightness = a3b_step42;
						break;
			case 83:
			case 84:	adjacent_brightness	= ab_step43;
						adjacent2_brightness = a2b_step43;
						adjacent3_brightness = a3b_step43;
						break;
			case 85:
			case 86:	adjacent_brightness	= ab_step44;
						adjacent2_brightness = a2b_step44;
						adjacent3_brightness = a3b_step44;
						break;
			case 87:
			case 88:	adjacent_brightness	= ab_step45;
						adjacent2_brightness = a2b_step45;
						adjacent3_brightness = a3b_step45;
						break;
			case 89:
			case 90:	adjacent_brightness	= ab_step46;
						adjacent2_brightness = a2b_step46;
						adjacent3_brightness = a3b_step46;
						break;
			case 91:
			case 92:	adjacent_brightness	= ab_step47;
						adjacent2_brightness = a2b_step47;
						adjacent3_brightness = a3b_step47;
						break;
			case 93:
			case 94:	adjacent_brightness	= ab_step48;
						adjacent2_brightness = a2b_step48;
						adjacent3_brightness = a3b_step48;
						break;
			case 95:
			case 96:	adjacent_brightness	= ab_step49;
						adjacent2_brightness = a2b_step49;
						adjacent3_brightness = a3b_step49;
						break;
			case 97:
			case 98:	adjacent_brightness	= ab_step50;
						adjacent2_brightness = a2b_step50;
						adjacent3_brightness = a3b_step50;
						break;
			case 99:
			case 100:	adjacent_brightness	= ab_step51;
						adjacent2_brightness = a2b_step51;
						adjacent3_brightness = a3b_step51;
						break;
		}

		strobe_lights(led_run);						// Check the lights.
		print_progress_bar(3, 5, percent);
}


void print_strobe_fadetime(unsigned char percent)
{
	unsigned char i;	


	switch (percent) {
		
			case 0:		oled.buffer[2][15] = ' ';		// 0s
						oled.buffer[2][16] = ' ';
						oled.buffer[2][17] = ' ';
						oled.buffer[2][18] = '0';
						oled.buffer[2][19] = 's';
						break;
			case 1:
			case 2:		oled.buffer[2][15] = ' ';		// 0.05s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 3:
			case 4:		oled.buffer[2][15] = '1';		// 0.10s
						oled.buffer[2][16] = '0';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 5:
			case 6:		oled.buffer[2][15] = '1';		// 0.15s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 7:
			case 8:		oled.buffer[2][15] = '2';		// 0.20s
						oled.buffer[2][16] = '0';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 9:
			case 10:	oled.buffer[2][15] = '2';		// 0.25s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 11:
			case 12:	oled.buffer[2][15] = '3';		// 0.30s
						oled.buffer[2][16] = '0';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 13:
			case 14:	oled.buffer[2][15] = '3';		// 0.35s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 15:
			case 16:	oled.buffer[2][15] = '4';		// 0.40s
						oled.buffer[2][16] = '0';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 17:
			case 18:	oled.buffer[2][15] = '4';		// 0.45s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 19:
			case 20:	oled.buffer[2][15] = '5';		// 0.50s
						oled.buffer[2][16] = '0';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 21:
			case 22:	oled.buffer[2][15] = '5';		// 0.55s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 23:
			case 24:	oled.buffer[2][15] = '6';		// 0.60s
						oled.buffer[2][16] = '0';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 25:
			case 26:	oled.buffer[2][15] = '6';		// 0.65s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 27:
			case 28:	oled.buffer[2][15] = '7';		// 0.70s
						oled.buffer[2][16] = '0';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 29:
			case 30:	oled.buffer[2][15] = '7';		// 0.75s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 31:
			case 32:	oled.buffer[2][15] = '8';		// 0.80s
						oled.buffer[2][16] = '0';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 33:
			case 34:	oled.buffer[2][15] = '8';		// 0.85s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 35:
			case 36:	oled.buffer[2][15] = '9';		// 0.90s
						oled.buffer[2][16] = '0';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 37:
			case 38:	oled.buffer[2][15] = '9';		// 0.95s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '0';
						oled.buffer[2][18] = 'm';
						oled.buffer[2][19] = 's';
						break;
			case 39:
			case 40:	oled.buffer[2][15] = ' ';		// 1s
						oled.buffer[2][16] = '1';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '0';
						oled.buffer[2][19] = 's';
						break;
			case 41:
			case 42:	oled.buffer[2][15] = ' ';		// 1.1s
						oled.buffer[2][16] = '1';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '1';
						oled.buffer[2][19] = 's';
						break;
			case 43:
			case 44:	oled.buffer[2][15] = ' ';		// 1.2s
						oled.buffer[2][16] = '1';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '2';
						oled.buffer[2][19] = 's';
						break;
			case 45:
			case 46:	oled.buffer[2][15] = ' ';		// 1.3s
						oled.buffer[2][16] = '1';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '3';
						oled.buffer[2][19] = 's';
						break;
			case 47:
			case 48:	oled.buffer[2][15] = ' ';		// 1.4s
						oled.buffer[2][16] = '1';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '4';
						oled.buffer[2][19] = 's';
						break;
			case 49:
			case 50:	oled.buffer[2][15] = ' ';		// 1.5s
						oled.buffer[2][16] = '1';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '5';
						oled.buffer[2][19] = 's';
						break;
			case 51:
			case 52:	oled.buffer[2][15] = ' ';		// 1.6s
						oled.buffer[2][16] = '1';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '6';
						oled.buffer[2][19] = 's';
						break;
			case 53:
			case 54:	oled.buffer[2][15] = ' ';		// 1.7s
						oled.buffer[2][16] = '1';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '7';
						oled.buffer[2][19] = 's';
						break;
			case 55:
			case 56:	oled.buffer[2][15] = ' ';		// 1.8s
						oled.buffer[2][16] = '1';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '8';
						oled.buffer[2][19] = 's';
						break;
			case 57:
			case 58:	oled.buffer[2][15] = ' ';		// 1.9s
						oled.buffer[2][16] = '1';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '9';
						oled.buffer[2][19] = 's';
						break;
			case 59:
			case 60:	oled.buffer[2][15] = ' ';		// 2.0s
						oled.buffer[2][16] = '2';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '0';
						oled.buffer[2][19] = 's';
						break;
			case 61:
			case 62:	oled.buffer[2][15] = ' ';		// 2.1s
						oled.buffer[2][16] = '2';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '1';
						oled.buffer[2][19] = 's';
						break;
			case 63:
			case 64:	oled.buffer[2][15] = ' ';		// 2.2s
						oled.buffer[2][16] = '2';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '2';
						oled.buffer[2][19] = 's';
						break;
			case 65:
			case 66:	oled.buffer[2][15] = ' ';		// 2.3s
						oled.buffer[2][16] = '2';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '3';
						oled.buffer[2][19] = 's';
						break;
			case 67:
			case 68:	oled.buffer[2][15] = ' ';		// 2.4s
						oled.buffer[2][16] = '2';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '4';
						oled.buffer[2][19] = 's';
						break;
			case 69:
			case 70:	oled.buffer[2][15] = ' ';		// 2.5s
						oled.buffer[2][16] = '2';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '5';
						oled.buffer[2][19] = 's';
						break;
			case 71:
			case 72:	oled.buffer[2][15] = ' ';		// 2.6s
						oled.buffer[2][16] = '2';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '6';
						oled.buffer[2][19] = 's';
						break;
			case 73:
			case 74:	oled.buffer[2][15] = ' ';		// 2.7s
						oled.buffer[2][16] = '2';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '7';
						oled.buffer[2][19] = 's';
						break;
			case 75:
			case 76:	oled.buffer[2][15] = ' ';		// 2.8s
						oled.buffer[2][16] = '2';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '8';
						oled.buffer[2][19] = 's';
						break;
			case 77:
			case 78:	oled.buffer[2][15] = ' ';		// 2.9s
						oled.buffer[2][16] = '2';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '9';
						oled.buffer[2][19] = 's';
						break;
			case 79:
			case 80:	oled.buffer[2][15] = ' ';		// 3.0s
						oled.buffer[2][16] = '3';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '0';
						oled.buffer[2][19] = 's';
						break;
			case 81:
			case 82:	oled.buffer[2][15] = ' ';		// 3.2s
						oled.buffer[2][16] = '3';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '2';
						oled.buffer[2][19] = 's';
						break;
			case 83:
			case 84:	oled.buffer[2][15] = ' ';		// 3.4s
						oled.buffer[2][16] = '3';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '4';
						oled.buffer[2][19] = 's';
						break;
			case 85:
			case 86:	oled.buffer[2][15] = ' ';		// 3.6s
						oled.buffer[2][16] = '3';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '6';
						oled.buffer[2][19] = 's';
						break;
			case 87:
			case 88:	oled.buffer[2][15] = ' ';		// 3.8s
						oled.buffer[2][16] = '3';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '8';
						oled.buffer[2][19] = 's';
						break;
			case 89:
			case 90:	oled.buffer[2][15] = ' ';		// 4.0s
						oled.buffer[2][16] = '4';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '0';
						oled.buffer[2][19] = 's';
						break;
			case 91:
			case 92:	oled.buffer[2][15] = ' ';		// 4.2s
						oled.buffer[2][16] = '4';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '2';
						oled.buffer[2][19] = 's';
						break;
			case 93:
			case 94:	oled.buffer[2][15] = ' ';		// 4.4s
						oled.buffer[2][16] = '4';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '4';
						oled.buffer[2][19] = 's';
						break;
			case 95:
			case 96:	oled.buffer[2][15] = ' ';		// 4.6s
						oled.buffer[2][16] = '4';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '6';
						oled.buffer[2][19] = 's';
						break;
			case 97:
			case 98:	oled.buffer[2][15] = ' ';		// 4.8s
						oled.buffer[2][16] = '4';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '8';
						oled.buffer[2][19] = 's';
						break;
			case 99:
			case 100:	oled.buffer[2][15] = ' ';		// 5.0s
						oled.buffer[2][16] = '5';
						oled.buffer[2][17] = '.';
						oled.buffer[2][18] = '0';
						oled.buffer[2][19] = 's';
						break;
			break;
		}

		strobe_lights(led_run);						// Check the lights.
		print_progress_bar(3, 5, percent);
		adc_fade_time = (float)(100 - percent) * 0.5;
}



