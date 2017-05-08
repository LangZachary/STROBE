

// This function prints a progress bar out to the OLED display. 
// row - 			The row of the display the progress bar will be printed on. 0 for top, 3 for bottom.
// start_position - The spot on the row the progress bar will start on. This position must be ten or more
//					characters from the right edge for the function to work correctly.
// percent -		How full the progress bar is. This number must be from 0 - 100 to display correctly.
void print_progress_bar(unsigned char row, unsigned char start_position, unsigned char percent)
{
	unsigned char i;	


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
						}

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
}

// This function prints the Timeout Delay for Motion Sensing mode in the Options.
// The length of the time out delay is printed in the top right corner of the OLED and the progress
// bar is printed in the centre of the second line down.
void print_ms_timeout_delay(unsigned char row, unsigned char start_position, unsigned char percent)
{

	unsigned char i;

	switch (percent) {
		
			case 0:		zone_timeout_delay = 0;							// 0s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 1:
			case 2:		zone_timeout_delay = 1;							// 0.1s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '1';
						oled.buffer[0][19] = 's';

						oled.buffer[row][start_position] = oled_load1;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 3:
			case 4:		zone_timeout_delay = 2;							// 0.2s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '2';
						oled.buffer[0][19] = 's';

						oled.buffer[row][start_position] = oled_load2;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 5:
			case 6:		zone_timeout_delay = 3;							// 0.3s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '3';
						oled.buffer[0][19] = 's';

						oled.buffer[row][start_position] = oled_load3;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						}

			case 7:
			case 8:		zone_timeout_delay = 4;							// 0.4s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '4';
						oled.buffer[0][19] = 's';

						oled.buffer[row][start_position] = oled_load4;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 9:
			case 10:	zone_timeout_delay = 5;							// 0.5s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 's';

						oled.buffer[row][start_position] = oled_load5;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 11:
			case 12:	zone_timeout_delay = 6;							// 0.6s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '6';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load1;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 13:
			case 14:	zone_timeout_delay = 7;							// 0.7s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '7';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load2;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 15:
			case 16:	zone_timeout_delay = 8;							// 0.8s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '8';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load3;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 17:
			case 18:	zone_timeout_delay = 9;							// 0.9s
						oled.buffer[0][16] = '0';
						oled.buffer[0][17] = '.';
						oled.buffer[0][18] = '9';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load4;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 19:
			case 20:	zone_timeout_delay = 10;						// 1s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '1';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load5;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 21:
			case 22:	zone_timeout_delay = 20;						// 2s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '2';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load1;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 23:
			case 24:	zone_timeout_delay = 30;						// 3s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '3';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load2;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 25:
			case 26:	zone_timeout_delay = 40;						// 4s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '4';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load3;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 27:
			case 28:	zone_timeout_delay = 50;						// 5s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load4;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 29:
			case 30:	zone_timeout_delay = 60;						// 6s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '6';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load5;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 31:
			case 32:	zone_timeout_delay = 70;						// 7s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '7';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load1;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 33:
			case 34:	zone_timeout_delay = 80;						// 8s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '8';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load2;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 35:
			case 36:	zone_timeout_delay = 90;						// 9s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '9';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load3;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 37:
			case 38:	zone_timeout_delay = 100;						// 10s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load4;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 39:
			case 40:	zone_timeout_delay = 120;						// 12s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '2';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load5;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 41:
			case 42:	zone_timeout_delay = 140;						// 14s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '4';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load1;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 43:
			case 44:	zone_timeout_delay = 160;						// 16s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '6';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load2;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 45:
			case 46:	zone_timeout_delay = 180;						// 18s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '8';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load3;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 47:
			case 48:	zone_timeout_delay = 200;						// 20s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load4;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 49:
			case 50:	zone_timeout_delay = 220;						// 22s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '2';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load5;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 51:
			case 52:	zone_timeout_delay = 240;						// 24s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '4';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load1;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 53:
			case 54:	zone_timeout_delay = 260;						// 26s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '6';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load2;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 55:
			case 56:	zone_timeout_delay = 280;						// 28s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '8';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load3;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 57:
			case 58:	zone_timeout_delay = 300;						// 30s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '3';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load4;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 59:
			case 60:	zone_timeout_delay = 350;						// 35s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '3';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load5;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 61:
			case 62:	zone_timeout_delay = 400;						// 40s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '4';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load1;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 63:
			case 64:	zone_timeout_delay = 450;						// 45s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '4';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load2;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 65:
			case 66:	zone_timeout_delay = 500;						// 50s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '5';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load3;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 67:
			case 68:	zone_timeout_delay = 550;						// 55s
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '5';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 's';

						for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load4;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 69:
			case 70:	zone_timeout_delay = 600;						// 1m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '1';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load5;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 71:
			case 72:	zone_timeout_delay = 1200;						// 2m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '2';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load1;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 73:
			case 74:	zone_timeout_delay = 1800;						// 3m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '3';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load2;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 75:
			case 76:	zone_timeout_delay = 2400;						// 4m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '4';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load3;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 77:
			case 78:	zone_timeout_delay = 3000;						// 5m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load4;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 79:
			case 80:	zone_timeout_delay = 3600;						// 6m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '6';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load5;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 81:
			case 82:	zone_timeout_delay = 4200;						// 7m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '7';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load1;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 83:
			case 84:	zone_timeout_delay = 4800;						// 8m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '8';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load2;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 85:
			case 86:	zone_timeout_delay = 5400;						// 9m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = ' ';
						oled.buffer[0][18] = '9';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load3;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 87:
			case 88:	zone_timeout_delay = 6000;						// 10m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load4;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 89:
			case 90:	zone_timeout_delay = 9000;						// 15m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load5;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 91:
			case 92:	zone_timeout_delay = 12000;						// 20m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load1;
						break;

			case 93:
			case 94:	zone_timeout_delay = 15000;						// 25m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '2';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load2;
						break;

			case 95:
			case 96:	zone_timeout_delay = 18000;						// 30m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '3';
						oled.buffer[0][18] = '0';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load3;
						break;

			case 97:
			case 98:	zone_timeout_delay = 27000;						// 45m
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '4';
						oled.buffer[0][18] = '5';
						oled.buffer[0][19] = 'm';

						for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load4;
						break;

			case 99:
			case 100:	zone_timeout_delay = 36000;						// 1hr
						oled.buffer[0][16] = ' ';
						oled.buffer[0][17] = '1';
						oled.buffer[0][18] = 'h';
						oled.buffer[0][19] = 'r';

						for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load5;
						break;
		}
}

// This function prints the Light Spread for the Motion Sensing mode in the Options menu.
// The progress bar for the Light Spread should be printed in the center of the bottom line of the OLED.
void print_ms_lightspread(unsigned char row, unsigned char start_position, unsigned char percent)
{
	unsigned char i;	


	switch (percent) {
		
			case 0:		adjacent_brightness	= ab_step1;
						adjacent2_brightness = a2b_step1;
						adjacent3_brightness = a3b_step1;

						for (i = 0; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 1:
			case 2:		adjacent_brightness	= ab_step2;
						adjacent2_brightness = a2b_step2;
						adjacent3_brightness = a3b_step2;

						oled.buffer[row][start_position] = oled_load1;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 3:
			case 4:		adjacent_brightness	= ab_step3;
						adjacent2_brightness = a2b_step3;
						adjacent3_brightness = a3b_step3;

						oled.buffer[row][start_position] = oled_load2;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 5:
			case 6:		adjacent_brightness	= ab_step4;
						adjacent2_brightness = a2b_step4;
						adjacent3_brightness = a3b_step4;

						oled.buffer[row][start_position] = oled_load3;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						}

			case 7:
			case 8:		adjacent_brightness	= ab_step5;
						adjacent2_brightness = a2b_step5;
						adjacent3_brightness = a3b_step5;

						oled.buffer[row][start_position] = oled_load4;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 9:
			case 10:	adjacent_brightness	= ab_step6;
						adjacent2_brightness = a2b_step6;
						adjacent3_brightness = a3b_step6;

						oled.buffer[row][start_position] = oled_load5;
						for (i = 1; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 11:
			case 12:	adjacent_brightness	= ab_step7;
						adjacent2_brightness = a2b_step7;
						adjacent3_brightness = a3b_step7;

						for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load1;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 13:
			case 14:	adjacent_brightness	= ab_step8;
						adjacent2_brightness = a2b_step8;
						adjacent3_brightness = a3b_step8;

						for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load2;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 15:
			case 16:	adjacent_brightness	= ab_step9;
						adjacent2_brightness = a2b_step9;
						adjacent3_brightness = a3b_step9;

						for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load3;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 17:
			case 18:	adjacent_brightness	= ab_step10;
						adjacent2_brightness = a2b_step10;
						adjacent3_brightness = a3b_step10;

						for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load4;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 19:
			case 20:	adjacent_brightness	= ab_step11;
						adjacent2_brightness = a2b_step11;
						adjacent3_brightness = a3b_step11;

						for (i = 0; i <= 0; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 1] = oled_load5;
						for (i = 2; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 21:
			case 22:	adjacent_brightness	= ab_step12;
						adjacent2_brightness = a2b_step12;
						adjacent3_brightness = a3b_step12;

						for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load1;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 23:
			case 24:	adjacent_brightness	= ab_step13;
						adjacent2_brightness = a2b_step13;
						adjacent3_brightness = a3b_step13;

						for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load2;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 25:
			case 26:	adjacent_brightness	= ab_step14;
						adjacent2_brightness = a2b_step14;
						adjacent3_brightness = a3b_step14;

						for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load3;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 27:
			case 28:	adjacent_brightness	= ab_step15;
						adjacent2_brightness = a2b_step15;
						adjacent3_brightness = a3b_step15;

						for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load4;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 29:
			case 30:	adjacent_brightness	= ab_step16;
						adjacent2_brightness = a2b_step16;
						adjacent3_brightness = a3b_step16;

						for (i = 0; i <= 1; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 2] = oled_load5;
						for (i = 3; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 31:
			case 32:	adjacent_brightness	= ab_step17;
						adjacent2_brightness = a2b_step17;
						adjacent3_brightness = a3b_step17;

						for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load1;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 33:
			case 34:	adjacent_brightness	= ab_step18;
						adjacent2_brightness = a2b_step18;
						adjacent3_brightness = a3b_step18;

						for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load2;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 35:
			case 36:	adjacent_brightness	= ab_step19;
						adjacent2_brightness = a2b_step19;
						adjacent3_brightness = a3b_step19;

						for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load3;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 37:
			case 38:	adjacent_brightness	= ab_step20;
						adjacent2_brightness = a2b_step20;
						adjacent3_brightness = a3b_step20;

						for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load4;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 39:
			case 40:	adjacent_brightness	= ab_step21;
						adjacent2_brightness = a2b_step21;
						adjacent3_brightness = a3b_step21;

						for (i = 0; i <= 2; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 3] = oled_load5;
						for (i = 4; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 41:
			case 42:	adjacent_brightness	= ab_step22;
						adjacent2_brightness = a2b_step22;
						adjacent3_brightness = a3b_step22;

						for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load1;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 43:
			case 44:	adjacent_brightness	= ab_step23;
						adjacent2_brightness = a2b_step23;
						adjacent3_brightness = a3b_step23;

						for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load2;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 45:
			case 46:	adjacent_brightness	= ab_step24;
						adjacent2_brightness = a2b_step24;
						adjacent3_brightness = a3b_step24;

						for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load3;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 47:
			case 48:	adjacent_brightness	= ab_step25;
						adjacent2_brightness = a2b_step25;
						adjacent3_brightness = a3b_step25;

						for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load4;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 49:
			case 50:	adjacent_brightness	= ab_step26;
						adjacent2_brightness = a2b_step26;
						adjacent3_brightness = a3b_step26;

						for (i = 0; i <= 3; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 4] = oled_load5;
						for (i = 5; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 51:
			case 52:	adjacent_brightness	= ab_step27;
						adjacent2_brightness = a2b_step27;
						adjacent3_brightness = a3b_step27;

						for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load1;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 53:
			case 54:	adjacent_brightness	= ab_step28;
						adjacent2_brightness = a2b_step28;
						adjacent3_brightness = a3b_step28;

						for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load2;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 55:
			case 56:	adjacent_brightness	= ab_step29;
						adjacent2_brightness = a2b_step29;
						adjacent3_brightness = a3b_step29;

						for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load3;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 57:
			case 58:	adjacent_brightness	= ab_step30;
						adjacent2_brightness = a2b_step30;
						adjacent3_brightness = a3b_step30;

						for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load4;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 59:
			case 60:	adjacent_brightness	= ab_step31;
						adjacent2_brightness = a2b_step31;
						adjacent3_brightness = a3b_step31;

						for (i = 0; i <= 4; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 5] = oled_load5;
						for (i = 6; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 61:
			case 62:	adjacent_brightness	= ab_step32;
						adjacent2_brightness = a2b_step32;
						adjacent3_brightness = a3b_step32;

						for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load1;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 63:
			case 64:	adjacent_brightness	= ab_step33;
						adjacent2_brightness = a2b_step33;
						adjacent3_brightness = a3b_step33;

						for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load2;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 65:
			case 66:	adjacent_brightness	= ab_step34;
						adjacent2_brightness = a2b_step34;
						adjacent3_brightness = a3b_step34;

						for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load3;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 67:
			case 68:	adjacent_brightness	= ab_step35;
						adjacent2_brightness = a2b_step35;
						adjacent3_brightness = a3b_step35;

						for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load4;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 69:
			case 70:	adjacent_brightness	= ab_step36;
						adjacent2_brightness = a2b_step36;
						adjacent3_brightness = a3b_step36;

						for (i = 0; i <= 5; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 6] = oled_load5;
						for (i = 7; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 71:
			case 72:	adjacent_brightness	= ab_step37;
						adjacent2_brightness = a2b_step37;
						adjacent3_brightness = a3b_step37;

						for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load1;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 73:
			case 74:	adjacent_brightness	= ab_step38;
						adjacent2_brightness = a2b_step38;
						adjacent3_brightness = a3b_step38;

						for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load2;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 75:
			case 76:	adjacent_brightness	= ab_step39;
						adjacent2_brightness = a2b_step39;
						adjacent3_brightness = a3b_step39;

						for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load3;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 77:
			case 78:	adjacent_brightness	= ab_step40;
						adjacent2_brightness = a2b_step40;
						adjacent3_brightness = a3b_step40;

						for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load4;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 79:
			case 80:	adjacent_brightness	= ab_step41;
						adjacent2_brightness = a2b_step41;
						adjacent3_brightness = a3b_step41;

						for (i = 0; i <= 6; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 7] = oled_load5;
						for (i = 8; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 81:
			case 82:	adjacent_brightness	= ab_step42;
						adjacent2_brightness = a2b_step42;
						adjacent3_brightness = a3b_step42;

						for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load1;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 83:
			case 84:	adjacent_brightness	= ab_step43;
						adjacent2_brightness = a2b_step43;
						adjacent3_brightness = a3b_step43;

						for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load2;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 85:
			case 86:	adjacent_brightness	= ab_step44;
						adjacent2_brightness = a2b_step44;
						adjacent3_brightness = a3b_step44;

						for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load3;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 87:
			case 88:	adjacent_brightness	= ab_step45;
						adjacent2_brightness = a2b_step45;
						adjacent3_brightness = a3b_step45;

						for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load4;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 89:
			case 90:	adjacent_brightness	= ab_step46;
						adjacent2_brightness = a2b_step46;
						adjacent3_brightness = a3b_step46;

						for (i = 0; i <= 7; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 8] = oled_load5;
						for (i = 9; i <= 9; i++) {
							oled.buffer[row][start_position + i] = ' ';	// Print spaces.
						} break;

			case 91:
			case 92:	adjacent_brightness	= ab_step47;
						adjacent2_brightness = a2b_step47;
						adjacent3_brightness = a3b_step47;

						for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load1;
						break;

			case 93:
			case 94:	adjacent_brightness	= ab_step48;
						adjacent2_brightness = a2b_step48;
						adjacent3_brightness = a3b_step48;

						for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load2;
						break;

			case 95:
			case 96:	adjacent_brightness	= ab_step49;
						adjacent2_brightness = a2b_step49;
						adjacent3_brightness = a3b_step49;

						for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load3;
						break;

			case 97:
			case 98:	adjacent_brightness	= ab_step50;
						adjacent2_brightness = a2b_step50;
						adjacent3_brightness = a3b_step50;

						for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load4;
						break;

			case 99:
			case 100:	adjacent_brightness	= ab_step51;
						adjacent2_brightness = a2b_step51;
						adjacent3_brightness = a3b_step51;

						for (i = 0; i <= 8; i++) {
							oled.buffer[row][start_position + i] = oled_load5;// Print blocks.
						}				
						oled.buffer[row][start_position + 9] = oled_load5;
						break;
		}
}

