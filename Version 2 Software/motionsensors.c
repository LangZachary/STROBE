/*****************************************************************************************
 *                                 MOTION SENSORS										 *
 *****************************************************************************************/

/*  Root function for motion sensors.
 */
void strobe_motionsensors(void)
{
	unsigned char i;
	static unsigned char ms1_set = 0;

	if (ms1 & !ms1_set) {
		
			zone_brightness_target[1].r = 100;
			zone_brightness_target[1].g = 100;
			zone_brightness_target[1].b = 100;
		
		
		ms1_set = 1;
	} else if (!ms1 & ms1_set) {

		for (i = 1; i <= 6; i++) {
			zone_brightness_target[i].r = 0;
			zone_brightness_target[i].g = 0;
			zone_brightness_target[i].b = 0;
		}
		
		ms1_set = 0;
	}
}

