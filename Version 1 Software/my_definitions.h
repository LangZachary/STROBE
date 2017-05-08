//*********************************************************************
//* Custom user defined variables for the registers in an PIC18F87K90 *
//*																	  *
//* Written by Zachary Lang                                           *
//* January 12, 2015                                               	  *
//*********************************************************************


/*****************************************************************************************
 *                                    BUTTONS											 *
 *****************************************************************************************/

#define		button_timer_flag	PIR5bits.TMR5IF	
#define		button_timer		T5CONbits.TMR5ON
#define		button_up			PORTBbits.RB4
#define		button_down			PORTBbits.RB5
#define		button_enter		PORTBbits.RB3
#define		button_menu			PORTBbits.RB2	

// Variable for keeping track of when the buttons are ready for another check.
// Set to 1 for 20ms, set to 25 for 500ms.
unsigned char	button_wait = 0;

#define			button_up_pressed		1
#define			button_down_pressed		2
#define			button_enter_pressed	3
#define			button_menu_pressed		4


	
/*****************************************************************************************
 *                                MOTION SENSORS										 *
 *****************************************************************************************/
#define 	ms1					PORTAbits.RA3	// RA3


// LEDS

#define		z1r				PORTHbits.RH6	// RH6
#define		z1g				PORTHbits.RH7	// RH7
#define		z1b				PORTFbits.RF2	// RH6
	
// LED DIM CONTROLS

// Duty Cycle Variables. 
// This number is reset to a value between 1-99 at the end of every cycle (10ms)
// and the associated LED turned on. It is then counted down (0.1ms) and when the
// count hits 1, the associated LED turned off.
unsigned int	red_brightness[13] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned int	green_brightness[13] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned int	blue_brightness[13] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

// Zone Pulse Width Counter.
// This number is reset at the end of every LED pulse.  It is then counted down (0.1ms)
// and when it hits 0, triggers a reloading of the Duty Cycle Variables, turns the
// associated LEDs on, and resets itself.
unsigned int	brightness_count[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// INTERRUPTS

#define		dim_change_flag			INTCONbits.TMR0IF	// Timer0 Interrupt flag.
#define		dim_change_time = 45535
#define		oled_timer				T3CONbits.TMR3ON	// Timer3 OFF / ON bit.
#define		oled_timer_delayh		TMR3H				// Timer3 Delay high byte.
#define		oled_timer_delayl		TMR3L				// 				low byte.
#define		oled_timer_flag			PIR2bits.TMR3IF		// Timer3 Interrupt flag.

/*****************************************************************************************
 *                                      OLED											 *
 *****************************************************************************************/

// Structure that stores a command character to be sent to the OLED.
typedef union command_data
{
	struct 
	{
		unsigned int b0:1;
		unsigned int b1:1;
		unsigned int b2:1;
		unsigned int b3:1;
		unsigned int b4:1;
		unsigned int b5:1;
		unsigned int b6:1;
		unsigned int b7:1;
	};
	struct {
		unsigned char byte:8;
	};
};

// Structure for the OLED display.
// menu -		10 char string for telling which menu is supposed to be displayed on the OLED.
// line - 		1-4 keeps track of the line of the display currently pointed at.
// position - 	1-20 keeps track of the position on the line currently pointed at.
// display - 	array that stores all of the characters sent to the display already
//			 	placed in their respective positions.
// buffer - 	array that stores all of the characters needing to be sent to the display
//			 	placed in their respective positions.
struct display_data
{
	unsigned char menu;
	unsigned char line;
	unsigned char position;
	unsigned char display[4][20];
	unsigned char buffer[4][20];
};
#pragma idata large_idata
struct display_data oled = {0};
#pragma idata

// Bit for telling if the OLED is ready to be sent more data.
// 1 - OLED is ready for more data.
// 0 - OLED has not waited a sufficient time for more data.
unsigned char oled_ready = 0;

// Bit for telling if the OLED has changed and needs new data to be sent to it.
// 1 - Menu changed, needs new data in the buffer.
// 0 - Menu has not changed.
unsigned char oled_changed = 1;

// Bit for telling the OLED there is new data in the buffer that needs to be moved.
// 1 - Buffer has new data.
// 0 - Display is fully updated.
unsigned char oled_buffer = 0;

// Serial Communication bits.
#define		scs			PORTCbits.RC2	// RC2
#define		sck			PORTCbits.SCK1	// RC3
#define		sdi			PORTCbits.SDI1	// RC4
#define		sdo			PORTCbits.SDO1	// RC5

// Menus
#define		main_menu1		0
far rom unsigned char main_menu1_l1[] = "   Welcome to the   ";
far rom unsigned char main_menu1_l2[] = "       STROBE       ";
far rom unsigned char main_menu1_l3[] = "        xxxx        ";
far rom unsigned char main_menu1_l4[] = "        1234        ";

#define		select_menu1	10
far rom unsigned char select_menu1_l1[] = " Choose a mode:     ";
far rom unsigned char select_menu1_l2[] = "  > Motion Sensing  ";
far rom unsigned char select_menu1_l3[] = "    Manual          ";
far rom unsigned char select_menu1_l4[] = "    Strobe          ";

#define		select_menu2	11
far rom unsigned char select_menu2_l1[] = " Choose a mode:     ";
far rom unsigned char select_menu2_l2[] = "    Motion Sensing  ";
far rom unsigned char select_menu2_l3[] = "  > Manual          ";
far rom unsigned char select_menu2_l4[] = "    Strobe          ";

#define		select_menu3	12
far rom unsigned char select_menu3_l1[] = " Choose a mode:     ";
far rom unsigned char select_menu3_l2[] = "    Motion Sensing  ";
far rom unsigned char select_menu3_l3[] = "    Manual          ";
far rom unsigned char select_menu3_l4[] = "  > Strobe          ";

#define		select_menu4	13
far rom unsigned char select_menu4_l1[] = " Choose a mode:     ";
far rom unsigned char select_menu4_l2[] = "    Manual          ";
far rom unsigned char select_menu4_l3[] = "    Strobe          ";
far rom unsigned char select_menu4_l4[] = "  > Options         ";

#define		select_menu5	14
far rom unsigned char select_menu5_l1[] = " Choose a mode:     ";
far rom unsigned char select_menu5_l2[] = "    Manual          ";
far rom unsigned char select_menu5_l3[] = "  > Strobe          ";
far rom unsigned char select_menu5_l4[] = "    Options         ";

#define		select_menu6	15
far rom unsigned char select_menu6_l1[] = " Choose a mode:     ";
far rom unsigned char select_menu6_l2[] = "  > Manual          ";
far rom unsigned char select_menu6_l3[] = "    Strobe          ";
far rom unsigned char select_menu6_l4[] = "    Options         ";

#define		motion_screen1	20
far rom unsigned char motion_screen1_l1[] = "   Motion Sensors   ";
far rom unsigned char motion_screen1_l2[] = "        ON          ";
far rom unsigned char motion_screen1_l3[] = "                    ";
far rom unsigned char motion_screen1_l4[] = "                    ";

#define		manual_screen1	30
far rom unsigned char manual_screen1_l1[] = "    Manual Mode     ";
far rom unsigned char manual_screen1_l2[] = "                    ";
far rom unsigned char manual_screen1_l3[] = "  > New             ";
far rom unsigned char manual_screen1_l4[] = "    Load            ";

#define		manual_screen2	31
far rom unsigned char manual_screen2_l1[] = "    Manual Mode     ";
far rom unsigned char manual_screen2_l2[] = "                    ";
far rom unsigned char manual_screen2_l3[] = "    New             ";
far rom unsigned char manual_screen2_l4[] = "  > Load            ";

#define		manual_new1		40
far rom unsigned char manual_new1_l1[] = "         Brightness ";
far rom unsigned char manual_new1_l2[] = " > Save      0      ";
far rom unsigned char manual_new1_l3[] = "           Color    ";
far rom unsigned char manual_new1_l4[] = "             0      ";

#define		manual_load1	60
far rom unsigned char manual_load1_l1[] = " > Profile 1        ";
far rom unsigned char manual_load1_l2[] = "   Profile 2        ";
far rom unsigned char manual_load1_l3[] = "   Profile 3        ";
far rom unsigned char manual_load1_l4[] = "   Profile 4        ";




