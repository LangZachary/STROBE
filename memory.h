
// This Header Pre-Configures the Program Memory with Light Shows.

// Manual Show
// Saved in Slot 4 of the Manual Mode.
// All of the Red lights are turned to 100%, the Green and Blue are 0%.
#pragma romdata manual4_config = 0x11FC0
far const rom unsigned char preset_manual_config[2] = {0, 0};

#pragma romdata manual4_name = 0x11FC2
far const rom unsigned char preset_manual_name[14] = "All Red!     ";

#pragma romdata manual4_red = 0x11FD0
far const rom unsigned char preset_manual_red[16] = {	100, 	100, 	100,	// Zone 1, 2, 3
													100,	100,	100,	// Zone 4, 5, 6
													100,	100,	100,	// Zone 7, 8, 9
													100,	100,	100,	// Zone 10, 11, 12
												0, 0, 0, 0};

#pragma romdata manual4_green = 0x11FE0
far const rom unsigned char preset_manual_green[16] = {	0, 		0, 		0,	// Zone 1, 2, 3
													0,		0,		0,	// Zone 4, 5, 6
													0,		0,		0,	// Zone 7, 8, 9
													0,		0,		0,	// Zone 10, 11, 12
												0, 0, 0, 0};

#pragma romdata manual4_blue = 0x11FF0
far const rom unsigned char preset_manual_blue[16] = {	0, 		0, 		0,	// Zone 1, 2, 3
													0,		0,		0,	// Zone 4, 5, 6
													0,		0,		0,	// Zone 7, 8, 9
													0,		0,		0,	// Zone 10, 11, 12
												0, 0, 0, 0};

#pragma romdata short4_config = 0x13800
far const rom unsigned char preset_short_config[16] = {6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#pragma romdata short4_name = 0x13810
far const rom unsigned char preset_short_name[16] = "Police Sirens ";

#pragma romdata short4_stage12 = 0x13820
/*//	SPINNING MULTI COLORED LIGHTS				// Zone		1	2	3	4	5	6	7	8	9	10	11	12
far const rom unsigned char preset_short_red1[16] = {		100,100,0,	0,	0,	0,	100,100,0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_short_green1[16] = {		0,	0,	100,100,0,	0,	0,	0,	100,100,0,	0,	10,	0,	0,	0};
far const rom unsigned char preset_short_blue1[16] = {		0,	0,	0,	0,	100,100,0,	0,	0,	0,	100,100,0,	0,	0,	0};
far const rom unsigned char preset_short_red2[16] = {		0,	100,100,0,	0,	0,	0,	100,100,0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_short_green2[16] = {		0,	0,	0,	100,100,0,	0,	0,	0,	100,100,0,	10,	0,	0,	0};
far const rom unsigned char preset_short_blue2[16] = {		100,0,	0,	0,	0,	100,100,0,	0,	0,	0,	100,0,	0,	0,	0};
far const rom unsigned char preset_short_empty1[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red3[16] = {		0,	0,	100,100,0,	0,	0,	0,	100,100,0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_short_green3[16] = {		0,	0,	0,	0,	100,100,0,	0,	0,	0,	100,100,10,	0,	0,	0};
far const rom unsigned char preset_short_blue3[16] = {		100,100,0,	0,	0,	0,	100,100,0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red4[16] = {		0,	0,	0,	100,100,0,	0,	0,	0,	100,100,0,	0,	1,	0,	0};
far const rom unsigned char preset_short_green4[16] = {		100,0,	0,	0,	0,	100,100,0,	0,	0,	0,	100,10,	0,	0,	0};
far const rom unsigned char preset_short_blue4[16] = {		0,	100,100,0,	0,	0,	0,	100,100,0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty3[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red5[16] = {		0,	0,	0,	0,	100,100,0,	0,	0,	0,	100,100,0,	1,	0,	0};
far const rom unsigned char preset_short_green5[16] = {		100,100,0,	0,	0,	0,	100,100,0,	0,	0,	0,	10,	0,	0,	0};
far const rom unsigned char preset_short_blue5[16] = {		0,	0,	100,100,0,	0,	0,	0,	100,100,0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red6[16] = {		100,0,	0,	0,	0,	100,100,0,	0,	0,	0,	100,0,	1,	0,	0};
far const rom unsigned char preset_short_green6[16] = {		0,	100,100,0,	0,	0,	0,	100,100,0,	0,	0,	10,	0,	0,	0};
far const rom unsigned char preset_short_blue6[16] = {		0,	0,	0,	100,100,0,	0,	0,	0,	100,100,0,	0,	0,	0,	0};
*/
/*  RED, BLUE, THEN GREEN ON OFF PULSE
far const rom unsigned char preset_short_red1[16] = {		100,100,100,100,100,100,100,100,100,100,100,100,0,	500,0,	0};
far const rom unsigned char preset_short_green1[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	15,	0,	0,	0};
far const rom unsigned char preset_short_blue1[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	500,0,	0};
far const rom unsigned char preset_short_green2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	15,	0,	0,	0};
far const rom unsigned char preset_short_blue2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty1[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red3[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	500,0,	0};
far const rom unsigned char preset_short_green3[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	10,	0,	0,	0};
far const rom unsigned char preset_short_blue3[16] = {		100,100,100,100,100,100,100,100,100,100,100,100,0,	0,	0,	0};
far const rom unsigned char preset_short_red4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	500,0,	0};
far const rom unsigned char preset_short_green4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	10,	0,	0,	0};
far const rom unsigned char preset_short_blue4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty3[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red5[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	500,0,	0};
far const rom unsigned char preset_short_green5[16] = {		100,100,100,100,100,100,100,100,100,100,100,100,5,	0,	0,	0};
far const rom unsigned char preset_short_blue5[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red6[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	500,0,	0};
far const rom unsigned char preset_short_green6[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	0,	0,	0};
far const rom unsigned char preset_short_blue6[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
*/
// POLICE SIRENS  BLUE and RED SPINNING
far const rom unsigned char preset_short_red1[16] = {		100,100,100,0,	0,	0,	100,100,100,0,	0,	0,	0,	13,0,	0};
far const rom unsigned char preset_short_green1[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	50,	0,	0,	0};
far const rom unsigned char preset_short_blue1[16] = {		0,	0,	0,	100,100,100,0,	0,	0,	100,100,100,0,	0,	0,	0};
far const rom unsigned char preset_short_red2[16] = {		0,	100,100,100,0,	0,	0,	100,100,100,0,	0,	0,	13,0,	0};
far const rom unsigned char preset_short_green2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	50,	0,	0,	0};
far const rom unsigned char preset_short_blue2[16] = {		100,0,	0,	0,	100,100,100,0,	0,	0,	100,100,0,	0,	0,	0};
far const rom unsigned char preset_short_empty1[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red3[16] = {		0,	0,	100,100,100,0,	0,	0,	100,100,100,0,	0,	13,0,	0};
far const rom unsigned char preset_short_green3[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	50,	0,	0,	0};
far const rom unsigned char preset_short_blue3[16] = {		100,100,0,	0,	0,	100,100,100,0,	0,	0,100,	0,	0,	0,	0};
far const rom unsigned char preset_short_red4[16] = {		0,	0,	0,	100,100,100,0,	0,	0,	100,100,100,0,	13,0,	0};
far const rom unsigned char preset_short_green4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	50,	0,	0,	0};
far const rom unsigned char preset_short_blue4[16] = {		100,100,100,0,	0,	0,	100,100,100,0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty3[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red5[16] = {		100,0,	0,	0,	100,100,100,0,	0,	0,	100,100,0,	13,0,	0};
far const rom unsigned char preset_short_green5[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	50,	0,	0,	0};
far const rom unsigned char preset_short_blue5[16] = {		0,	100,100,100,0,	0,	0,	100,100,100,0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red6[16] = {		100,100,0,	0,	0,	100,100,100,0,	0,	0,	0,	0,	13,0,	0};
far const rom unsigned char preset_short_green6[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	50,	0,	0,	0};
far const rom unsigned char preset_short_blue6[16] = {		0,	0,	100,100,100,0,	0,	0,	100,100,100,0,	0,	0,	0,	0};
/*
 // STROBE
far const rom unsigned char preset_short_red1[16] = {		100,100,100,100,100,100,100,100,100,100,100,100,0,	5,	0,	0};
far const rom unsigned char preset_short_green1[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	20,	0,	0,	0};
far const rom unsigned char preset_short_blue1[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	45,	0,	0};
far const rom unsigned char preset_short_green2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	20,	0,	0,	0};
far const rom unsigned char preset_short_blue2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty1[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red3[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	0,	0};
far const rom unsigned char preset_short_green3[16] = {		100,100,100,100,100,100,100,100,100,100,100,100,20,	0,	0,	0};
far const rom unsigned char preset_short_blue3[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	45,	0,	0};
far const rom unsigned char preset_short_green4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	20,	0,	0,	0};
far const rom unsigned char preset_short_blue4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty3[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_empty4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_short_red5[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	5,	0,	0};
far const rom unsigned char preset_short_green5[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	20,	0,	0,	0};
far const rom unsigned char preset_short_blue5[16] = {		100,100,100,100,100,100,100,100,100,100,100,100,0,	0,	0,	0};
far const rom unsigned char preset_short_red6[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	45,	0,	0};
far const rom unsigned char preset_short_green6[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	20,	0,	0,	0};
far const rom unsigned char preset_short_blue6[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
*/

#pragma romdata long_stage1 = 0x1D000
far const rom unsigned char preset_long_config[16] = {20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#pragma romdata long_stage2 = 0x1D010
far const rom unsigned char preset_long_name[16] = "Presentation  ";

#pragma romdata long_stage3 = 0x1D020
// POLICE SIRENS  BLUE and RED SPINNING
far const rom unsigned char preset_long_red1[16] = {		20,	50,	70,	50,	10,	0,	0,	10,	50,	70,	50,	20,	0,	1,	0,	0};
far const rom unsigned char preset_long_green1[16] = {		0,	0,	20,	10,	10,	20,	20,	10,	10,	20,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue1[16] = {		10,	0,	10,	30,	30,	40,	40,	30,	30,	10,	0,	10,	0,	0,	0,	0};
far const rom unsigned char preset_long_red2[16] = {		60,	20,	50,	70,	50,	10,	10,	50,	70,	50,	20,	60,	0,	1,	0,	0};
far const rom unsigned char preset_long_green2[16] = {		10,	0,	0,	20,	10,	10,	10,	10,	20,	0,	0,	10,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue2[16] = {		0,	10,	0,	10,	30,	30,	30,	30,	10,	0,	10,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty1[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty2[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red3[16] = {		100,60,	20,	50,	70,	50,	50,	70,	50,	20,	60,	100,0,	1,	0,	0};
far const rom unsigned char preset_long_green3[16] = {		0,	10,	0,	0,	20,	10,	10,	20,	0,	0,	10,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue3[16] = {		20,	0,	10,	0,	10,	30,	30,	10,	0,	10,	0,	20,	0,	0,	0,	0};
far const rom unsigned char preset_long_red4[16] = {		60,	100,60,	20,	50,	70,	70,	50,	20,	60,	100,60,	0,	1,	0,	0};
far const rom unsigned char preset_long_green4[16] = {		20,	0,	10,	0,	0,	20,	20,	0,	0,	10,	0,	20,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue4[16] = {		0,	20,	0,	10,	0,	10,	10,	0,	10,	0,	20,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty3[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty4[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red5[16] = {		20,	60,	100,60,	20,	50,	50,	20,	60,	100,60,	20,	0,	1,	0,	0};
far const rom unsigned char preset_long_green5[16] = {		60,	20,	0,	10,	0,	0,	0,	0,	10,	0,	20,	60,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue5[16] = {		0,	0,	20,	0,	10,	0,	0,	10,	0,	20,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red6[16] = {		0,	20,	60,	100,60,	20,	20,	60,	100,60,	20,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green6[16] = {		90,	60,	20,	0,	10,	0,	0,	10,	0,	20,	60,	90,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue6[16] = {		0,	0,	0,	20,	0,	10,	10,	0,	20,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty5[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty6[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red7[16] = {		10,	0,	20,	60,	100,60,	60,	100,60,	20,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green7[16] = {		60,	90,	60,	20,	0,	10,	10,	0,	20,	60,	90,	60,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue7[16] = {		0,	0,	0,	0,	20,	0,	0,	20,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red8[16] = {		10,	10,	0,	20,	60,	100,100,60,	20,	0,	10,	10,	0,	1,	0,	0};
far const rom unsigned char preset_long_green8[16] = {		20,	60,	90,	60,	20,	0,	0,	20,	60,	90,	60,	20,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue8[16] = {		20,	0,	0,	0,	0,	20,	20,	0,	0,	0,	0,	20,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty7[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty8[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red9[16] = {		10,	10,	10,	0,	20,	60,	60,	20,	0,	10,	10,	10,	0,	1,	0,	0};
far const rom unsigned char preset_long_green9[16] = {		0,	20,	60,	90,	60,	20,	20,	60,	90,	60,	20,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue9[16] = {		60,	20,	0,	0,	0,	0,	0,	0,	0,	0,	20,	60,	0,	0,	0,	0};
far const rom unsigned char preset_long_red10[16] = {		10,	10,	10,	10,	0,	20,	20,	0,	10,	10,	10,	10,	0,	1,	0,	0};
far const rom unsigned char preset_long_green10[16] = {		0,	0,	20,	60,	90,	60,	60,	90,	60,	20,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue10[16] = {		90,	60,	20,	0,	0,	0,	0,	0,	0,	20,	60,	90,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty9[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty10[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red11[16] = {		30,	10,	10,	10,	10,	0,	0,	10,	10,	10,	10,	30,	0,	1,	0,	0};
far const rom unsigned char preset_long_green11[16] = {		0,	0,	0,	20,	60,	90,	90,	60,	20,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue11[16] = {		40,	90,	60,	20,	0,	0,	0,	0,	20,	60,	90,	40,	0,	0,	0,	0};
far const rom unsigned char preset_long_red12[16] = {		40,	30,	10,	10,	10,	10,	10,	10,	10,	10,	30,	40,	0,	1,	0,	0};
far const rom unsigned char preset_long_green12[16] = {		10,	0,	0,	0,	20,	60,	60,	20,	0,	0,	0,	10,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue12[16] = {		20,	40,	90,	60,	20,	0,	0,	20,	60,	90,	40,	20,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty11[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty12[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red13[16] = {		50,	30,	10,	10,	10,	10,	10,	10,	10,	10,	30,	50,	0,	1,	0,	0};
far const rom unsigned char preset_long_green13[16] = {		20,	10,	0,	0,	0,	20,	20,	0,	0,	0,	10,	20,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue13[16] = {		10,	20,	40,	90,	60,	20,	20,	60,	90,	40,	20,	10,	0,	0,	0,	0};
far const rom unsigned char preset_long_red14[16] = {		60,	50,	30,	10,	10,	10,	10,	10,	10,	30,	50,	60,	0,	1,	0,	0};
far const rom unsigned char preset_long_green14[16] = {		50,	20,	10,	0,	0,	0,	0,	0,	0,	10,	20,	50,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue14[16] = {		0,	10,	20,	40,	90,	60,	60,	90,	40,	20,	10,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty13[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty14[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red15[16] = {		10,	50,	30,	10,	10,	10,	10,	10,	10,	30,	50,	10,	0,	1,	0,	0};
far const rom unsigned char preset_long_green15[16] = {		80,	50,	20,	10,	0,	0,	0,	0,	10,	20,	50,	80,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue15[16] = {		20,	0,	10,	20,	40,	90,	90,	40,	20,	10,	0,	20,	0,	0,	0,	0};
far const rom unsigned char preset_long_red16[16] = {		0,	10,	50,	30,	10,	10,	10,	10,	30,	50,	10,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green16[16] = {		20,	80,	50,	20,	10,	0,	0,	10,	20,	50,	80,	20,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue16[16] = {		40,	20,	0,	10,	20,	40,	40,	20,	10,	0,	20,	40,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty15[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty16[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red17[16] = {		10,	0,	10,	50,	30,	10,	10,	30,	50,	10,	0,	10,	0,	1,	0,	0};
far const rom unsigned char preset_long_green17[16] = {		10,	20,	80,	50,	20,	10,	10,	20,	50,	80,	20,	10,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue17[16] = {		30,	40,	20,	0,	10,	20,	20,	10,	0,	20,	40,	30,	0,	0,	0,	0};
far const rom unsigned char preset_long_red18[16] = {		50,	10,	0,	10,	50,	30,	30,	50,	10,	0,	10,	50,	0,	1,	0,	0};
far const rom unsigned char preset_long_green18[16] = {		10,	10,	20,	80,	50,	20,	20,	50,	80,	20,	10,	10,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue18[16] = {		30,	30,	40,	20,	0,	10,	10,	0,	20,	40,	30,	30,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty17[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty18[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red19[16] = {		70,	50,	10,	0,	10,	50,	50,	10,	0,	10,	50,	70,	0,	1,	0,	0};
far const rom unsigned char preset_long_green19[16] = {		20,	10,	10,	20,	80,	50,	50,	80,	20,	10,	10,	20,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue19[16] = {		10,	30,	30,	40,	20,	0,	0,	20,	40,	30,	30,	10,	0,	0,	0,	0};
far const rom unsigned char preset_long_red20[16] = {		50,	70,	50,	10,	0,	10,	10,	0,	10,	50,	70,	50,	0,	1,	0,	0};
far const rom unsigned char preset_long_green20[16] = {		0,	20,	10,	10,	20,	80,	80,	20,	10,	10,	20,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue20[16] = {		0,	10,	30,	30,	40,	20,	20,	40,	30,	30,	10,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty19[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty20[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red21[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green21[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue21[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red22[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green22[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue22[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty21[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty22[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red23[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green23[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue23[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red24[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green24[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue24[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty23[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty24[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red25[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green25[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue25[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red26[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green26[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue26[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty25[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty26[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red27[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green27[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue27[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red28[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green28[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue28[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty27[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty28[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red29[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green29[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue29[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red30[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green30[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue30[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty29[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty30[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red31[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green31[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue31[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red32[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green32[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue32[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty31[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty32[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red33[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green33[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue33[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red34[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green34[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue34[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty33[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty34[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red35[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green35[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue35[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red36[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green36[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue36[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty35[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty36[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red37[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green37[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue37[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red38[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green38[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue38[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty37[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty38[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red39[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green39[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue39[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red40[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green40[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue40[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty39[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty40[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red41[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green41[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue41[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red42[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green42[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue42[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty41[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty42[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red43[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green43[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue43[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red44[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green44[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue44[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty43[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty44[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red45[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green45[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue45[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red46[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green46[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue46[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty45[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty46[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red47[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green47[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue47[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red48[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green48[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue48[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty47[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty48[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red49[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green49[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue49[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_red50[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0};
far const rom unsigned char preset_long_green50[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	48,	0,	0,	0};
far const rom unsigned char preset_long_blue50[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty49[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};
far const rom unsigned char preset_long_empty50[16] = {		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0};


// Return to the beginning of program memory to place the rest of the code.
#pragma code beginning=0x28

