/*****************************************************************************************
 *                                      WELCOME											 *
 *****************************************************************************************/

/*  This function presents controls the welcome screen of the device.
 *  A welcome screen will appear that describes the name of the device and a loading bar
 *  will appear across the bottom of the screen.  The loading bar will rise from zero to
 *  100 and imitate the loading of system software.
 *  The function will then go directly into the Main Menu of the Strobe.
 */
void strobe_welcome(void)
{
	static unsigned char 	load_percent = 0;
	unsigned char			load_enable;	

	// Initialize the display with the Welcome Screen 1.
	oled.menu = welcome_screen1;
	strobe_oled(oled_menu, 0, 0);

	// Initialize the values and start the timer.
	load_percent = 0;
	load_timer = 1;
	load_enable = 1;
	load_count = 1000;
	load_ready = 0;

	// Loading Screen
	do {

		if (load_ready) {

			if (load_percent > 100) {

				load_enable = 0;
				load_count = 5000;

			} else {

				welcome_load(&load_percent);
		
			}

			load_ready = 0;

		}

		if (buttons_check() == button_enter_pressed) {
			load_percent = 100;
		}

		strobe_oled(oled_run, 0, 0);

	} while (load_enable);

	// Clear the screen.
	strcpypgm2ram((char *)oled.buffer[0], welcome_screen2_l1);
 	strcpypgm2ram((char *)oled.buffer[1], welcome_screen2_l2);
	strcpypgm2ram((char *)oled.buffer[2], welcome_screen2_l3);
	strcpypgm2ram((char *)oled.buffer[3], welcome_screen2_l4);

	while(!load_ready){
		strobe_oled(oled_run, 0, 0);
	}
	
	oled.menu = select_menu1a;
	strobe_oled(oled_menu, 0, 0);

}

// This function prints out Welcome to the Strobe in a cool way.
void welcome_message(void)
{



}

// This function increments the percentage and then loads the needed delay for
// that percentage loaded.  At different increments the loading message will change.
// The numeric value of the percent will be loaded into the display on the top line
// beside loading...
void welcome_load(unsigned char *percent)
{
	unsigned char z;


	// Depending on the current percentage, a delay will be set.
	// Delay = 2ms * load_count.
	switch (*percent) {

		case 0:	load_count = 500;			// 0% - 1s.
				break;
		case 1:	load_count = 500;			// 1% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load1_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load1_l2);
				break;
		case 2:	load_count = 200;			// 2% - 1s.
				break;
		case 3:	load_count = 250;			// 3% - 1s.
				break;
		case 4:	load_count = 100;			// 4% - 1s.
				break;
		case 5:	load_count = 50;			// 5% - 1s.
				break;
		case 6:	load_count = 800;			// 6% - 1s.
				break;
		case 7:	load_count = 1000;			// 7% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load2_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load2_l2);
				break;
		case 8:	load_count = 1000;			// 8% - 1s.
				break;
		case 9:	load_count = 50;			// 9% - 1s.
				break;
		case 10:load_count = 150;			// 10% - 1s.
				break;
		case 11:load_count = 150;			// 11% - 1s.
				break;
		case 12:load_count = 150;			// 12% - 1s.
				break;
		case 13:load_count = 100;			// 13% - 1s.
				break;
		case 14:load_count = 500;			// 14% - 1s.
				break;
		case 15:load_count = 1000;			// 15% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load3_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load3_l2);
				break;
		case 16:load_count = 900;			// 16% - 1s.
				break;
		case 17:load_count = 400;			// 17% - 1s.
				break;
		case 18:load_count = 400;			// 18% - 1s.
				break;
		case 19:load_count = 200;			// 19% - 1s.
				break;
		case 20:load_count = 50;			// 20% - 1s.
				break;
		case 21:load_count = 80;			// 21% - 1s.
				break;
		case 22:load_count = 80;			// 22% - 1s.
				break;
		case 23:load_count = 80;			// 23% - 1s.
				break;
		case 24:load_count = 100;			// 24% - 1s.
				break;
		case 25:load_count = 250;			// 25% - 1s.
				break;
		case 26:load_count = 250;			// 26% - 1s.
				break;
		case 27:load_count = 1000;			// 27% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load4_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load4_l2);
				break;
		case 28:load_count = 2000;			// 28% - 1s.
				break;
		case 29:load_count = 100;			// 29% - 1s.
				break;
		case 30:load_count = 150;			// 30% - 1s.
				break;
		case 31:load_count = 150;			// 31% - 1s.
				break;
		case 32:load_count = 300;			// 32% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load5_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load5_l2);
				break;
		case 33:load_count = 300;			// 33% - 1s.
				break;
		case 34:load_count = 300;			// 34% - 1s.
				break;
		case 35:load_count = 300;			// 35% - 1s.
				break;
		case 36:load_count = 300;			// 36% - 1s.
				break;
		case 37:load_count = 300;			// 37% - 1s.
				break;
		case 38:load_count = 300;			// 38% - 1s.
				break;
		case 39:load_count = 300;			// 39% - 1s.
				break;
		case 40:load_count = 300;			// 40% - 1s.
				break;
		case 41:load_count = 300;			// 41% - 1s.
				break;
		case 42:load_count = 300;			// 42% - 1s.
				break;
		case 43:load_count = 300;			// 43% - 1s.
				break;
		case 44:load_count = 300;			// 44% - 1s.
				break;
		case 45:load_count = 300;			// 45% - 1s.
				break;
		case 46:load_count = 300;			// 46% - 1s.
				break;
		case 47:load_count = 300;			// 47% - 1s.
				break;
		case 48:load_count = 150;			// 48% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load6_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load6_l2);
				break;
		case 49:load_count = 150;			// 49% - 1s.
				break;
		case 50:load_count = 150;			// 50% - 1s.
				break;
		case 51:load_count = 150;			// 51% - 1s.
				break;
		case 52:load_count = 150;			// 52% - 1s.
				break;
		case 53:load_count = 150;			// 53% - 1s.
				break;
		case 54:load_count = 150;			// 54% - 1s.
				break;
		case 55:load_count = 150;			// 55% - 1s.
				break;
		case 56:load_count = 150;			// 56% - 1s.
				break;
		case 57:load_count = 150;			// 57% - 1s.
				break;
		case 58:load_count = 150;			// 58% - 1s.
				break;
		case 59:load_count = 150;			// 59% - 1s.
				break;
		case 60:load_count = 150;			// 60% - 1s.
				break;
		case 61:load_count = 50;			// 61% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load7_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load7_l2);
				break;
		case 62:load_count = 50;			// 62% - 1s.
				break;
		case 63:load_count = 50;			// 63% - 1s.
				break;
		case 64:load_count = 50;			// 64% - 1s.
				break;
		case 65:load_count = 50;			// 65% - 1s.
				break;
		case 66:load_count = 50;			// 66% - 1s.
				break;
		case 67:load_count = 50;			// 67% - 1s.
				break;
		case 68:load_count = 4000;			// 68% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load8_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load8_l2);
				break;
		case 69:load_count = 600;			// 69% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load9_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load9_l2);
				break;
		case 70:load_count = 250;			// 70% - 1s.
				break;
		case 71:load_count = 100;			// 71% - 1s.
				break;
		case 72:load_count = 300;			// 72% - 1s.
				break;
		case 73:load_count = 350;			// 73% - 1s.
				break;
		case 74:load_count = 250;			// 74% - 1s.
				break;
		case 75:load_count = 200;			// 75% - 1s.
				break;
		case 76:load_count = 200;			// 76% - 1s.
				break;
		case 77:load_count = 600;			// 77% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load10_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load10_l2);
				break;
		case 78:load_count = 800;			// 78% - 1s.
				break;
		case 79:load_count = 700;			// 79% - 1s.
				break;
		case 80:load_count = 800;			// 80% - 1s.
				break;
		case 81:load_count = 800;			// 81% - 1s.
				break;
		case 82:load_count = 200;			// 82% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load11_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load11_l2);
				break;
		case 83:load_count = 300;			// 83% - 1s.
				break;
		case 84:load_count = 300;			// 84% - 1s.
				break;
		case 85:load_count = 400;			// 85% - 1s.
				break;
		case 86:load_count = 200;			// 86% - 1s.
				break;
		case 87:load_count = 200;			// 87% - 1s.
				break;
		case 88:load_count = 200;			// 88% - 1s.
				break;
		case 89:load_count = 100;			// 89% - 1s.
				break;
		case 90:load_count = 100;			// 90% - 1s.
				break;
		case 91:load_count = 100;			// 91% - 1s.
				break;
		case 92:load_count = 100;			// 92% - 1s.
				break;
		case 93:load_count = 100;			// 93% - 1s.
				break;
		case 94:load_count = 100;			// 94% - 1s.
				break;
		case 95:load_count = 100;			// 95% - 1s.
				break;
		case 96:load_count = 750;			// 96% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load12_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load12_l2);
				break;
		case 97:load_count = 600;			// 97% - 1s.
				break;
		case 98:load_count = 600;			// 98% - 1s.
				break;
		case 99:load_count = 600;			// 99% - 1s.
				break;
		case 100:load_count = 2000;			// 100% - 1s.
			 	strcpypgm2ram((char *)oled.buffer[1], welcome_load13_l1);
			 	strcpypgm2ram((char *)oled.buffer[2], welcome_load13_l2);
				break;
	}

	// < 100% - Write out the stage number.	
	if (*percent < 100) {

		// Print the tens.
		z = ((float)*percent * 0.1);
		if (z > 0) {
			oled.buffer[0][16] = z + 0x30;
		}

		// Print the ones.
		z = *percent - (z * 10);
		oled.buffer[0][17] = z + 0x30;

	 // At 100% - Print Done.
	} else {

		oled.buffer[0][15] = 'D';
		oled.buffer[0][16] = 'o';
		oled.buffer[0][17] = 'n';
		oled.buffer[0][18] = 'e';
	}

	// Print the new loading bar to the display.
	print_progress_bar(3, 5, *percent);

	// Increment the percent for the next run.
	*percent = *percent + 1;

}

