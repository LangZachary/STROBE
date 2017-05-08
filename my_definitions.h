//*********************************************************************
//* Custom user defined variables for the registers in an PIC18F87K90 *
//*																	  *
//* Written by Zachary Lang                                           *
//* April 23, 2015                                               	  *
//*********************************************************************


/*****************************************************************************************
 *                                    WELCOME											 *
 *****************************************************************************************/






/*****************************************************************************************
 *                                    BUTTONS											 *
 *****************************************************************************************/

// Definitions //

#define		button_up			PORTBbits.RB4		// Up signal from button.
#define		button_down			PORTBbits.RB5		// Down signal from button.
#define		button_enter		PORTBbits.RB3		// Enter signal from button.
#define		button_menu			PORTBbits.RB2		// Menu signal from button.

#define		button_up_pressed		1				// States for button_pressed var in
#define		button_down_pressed		2				// function strobe_buttons().
#define		button_enter_pressed	3				// Menu is changed based on the
#define		button_menu_pressed		4				// button pressed.

#define		button_delay_20ms		1				// 1 * 20ms = 20ms.
#define		button_delay_80ms		4				// 4 * 20ms = 80ms.
#define		button_delay_300ms		15				// 15 * 20ms = 300ms.

// Variables //

// Keeps track of when the buttons are ready for another check. 1 >> 20ms, 25 >> 500ms.
#pragma idata INTERRUPTS
static unsigned char	button_wait = 0;

	
/*****************************************************************************************
 *                                MOTION SENSORS										 *
 *****************************************************************************************/

// Definitions //

// Process definitions that get passed into the strobe_motionsensors().


#define		ms_init			1
#define		ms_check		2
#define		ms_action		3
#define		ms_deinit		4

#define 	ms1					PORTAbits.RA3
#define		ms2					PORTAbits.RA2
#define		ms3					PORTAbits.RA5
#define		ms4					PORTAbits.RA4
#define		ms5					PORTCbits.RC1
#define		ms6					PORTCbits.RC0
#define		ms7					PORTCbits.RC6
#define		ms8					PORTCbits.RC7
#define		ms9					PORTJbits.RJ4
#define		ms10				PORTJbits.RJ5
#define		ms11				PORTJbits.RJ6
#define		ms12				PORTJbits.RJ7

// Delay between motion sensor checks. Frequency = ms_delay * 20ms. (default 100ms)
#define		ms_delay		5


// Variables //

// Bit for telling if the motion sensors are ready to be checked again. Default 100ms.
// 1 - Motion sensors are ready to be checked.
// 0 - Motion sensors have not waited a sufficient time to be checked.
static unsigned char	ms_ready = 0;

// Counting veriable used by the timer.
static unsigned char	ms_count = 0;

// Bit for telling whether motion sensor tracking mode is on or off.
static unsigned char	ms_tracking = 0;

#pragma idata LIGHTS
// Adjustable time out delay setting for the motion sensors.  This value is changed by the user.
static unsigned int	zone_timeout_delay = 10;
static unsigned int	zone_timeout_delay_old = 0;

// Adjacent Zone Brightness.
// 100 being maximum brightness and 0 being off.
static unsigned char	adjacent_brightness	= 20;
static unsigned char	adjacent2_brightness = 5;
static unsigned char	adjacent3_brightness = 0;
static unsigned char	adjacent_brightness_old	= 0;
static unsigned char	adjacent2_brightness_old = 0;
static unsigned char	adjacent3_brightness_old = 0;


/*****************************************************************************************
 *                                     LEDS      										 *
 *****************************************************************************************/

// Definitions //

// Process definitions that get passed into the strobe_lights().

#define		led_ms_init				1
#define		led_manual_init			2
#define		led_stage_init			3
#define		led_run					4
#define		led_deinit				5

#define		z1r				LATHbits.LATH6 // Zone 1 - 	Red
#define		z1g				LATHbits.LATH7 //			Green
#define		z1b				LATFbits.LATF2 //			Blue
#define		z2r				LATFbits.LATF3 // Zone 2 -	Red
#define		z2g				LATFbits.LATF4 //			Green
#define		z2b				LATFbits.LATF5 //			Blue
#define		z3r				LATFbits.LATF6 // Zone 3 -	Red
#define		z3g				LATFbits.LATF7 //			Green
#define		z3b				LATGbits.LATG3 //			Blue
#define		z4r				LATGbits.LATG2 // Zone 4 -	Red
#define		z4g				LATGbits.LATG1 //			Green
#define		z4b				LATGbits.LATG0 //			Blue
#define		z5r				LATEbits.LATE0 // Zone 5 -	Red
#define		z5g				LATEbits.LATE1 //			Green
#define		z5b				LATHbits.LATH3 //			Blue
#define		z6r				LATHbits.LATH2 // Zone 6 -	Red
#define		z6g				LATHbits.LATH1 //			Green
#define		z6b				LATHbits.LATH0 //			Blue
#define		z7r				LATEbits.LATE3 // Zone 7 -	Red
#define		z7g				LATEbits.LATE4 //			Green
#define		z7b				LATEbits.LATE5 //			Blue
#define		z8r				LATEbits.LATE6 // Zone 8 - 	Red
#define		z8g				LATEbits.LATE7 //			Green
#define		z8b				LATDbits.LATD0 //			Blue
#define		z9r				LATDbits.LATD1 // Zone 9 -	Red
#define		z9g				LATDbits.LATD2 //			Green
#define		z9b				LATDbits.LATD3 //			Blue
#define		z10r			LATDbits.LATD4 // Zone 10 -	Red
#define		z10g			LATDbits.LATD5 //			Green
#define		z10b			LATDbits.LATD6 //			Blue
#define		z11r			LATDbits.LATD7 // Zone 11 -	Red
#define		z11g			LATJbits.LATJ0 //			Green
#define		z11b			LATJbits.LATJ1 //			Blue
#define		z12r			LATJbits.LATJ2 // Zone 12 -	Red
#define		z12g			LATJbits.LATJ3 //			Green
#define		z12b			LATBbits.LATB0 //			Blue

// Fading //
// Percentage of the total desired light brightness change that
// each step will change the brightness by.
#define		fade_speed0		0.001666667		// 5.0s
#define		fade_speed1		0.001736111		// 4.8s
#define		fade_speed2		0.001811594		// 4.6s
#define		fade_speed3		0.001893939		// 4.4s
#define		fade_speed4		0.001984127		// 4.2s
#define		fade_speed5		0.002083333		// 4.0s
#define		fade_speed6		0.002192982		// 3.8s
#define		fade_speed7		0.002314815		// 3.6s
#define		fade_speed8		0.002450980		// 3.4s
#define		fade_speed9		0.002604167		// 3.2s
#define		fade_speed10	0.002777778		// 3.0s
#define		fade_speed11	0.002873563		// 2.9s
#define		fade_speed12	0.002976190		// 2.8s
#define		fade_speed13	0.003086415		// 2.7s
#define		fade_speed14	0.003205128		// 2.6s
#define		fade_speed15	0.003333333		// 2.5s
#define		fade_speed16	0.003472222		// 2.4s
#define		fade_speed17	0.003623188		// 2.3s
#define		fade_speed18	0.003787829		// 2.2s
#define		fade_speed19	0.003968254		// 2.1s
#define		fade_speed20	0.004166667		// 2s
#define		fade_speed21	0.004385965		// 1.9s
#define		fade_speed22	0.004629630		// 1.8s
#define		fade_speed23	0.004901961		// 1.7s
#define		fade_speed24	0.005208333		// 1.6s
#define		fade_speed25	0.005555556		// 1.5s
#define		fade_speed26	0.005952381		// 1.4s
#define		fade_speed27	0.006410256		// 1.3s
#define		fade_speed28	0.006944444		// 1.2s
#define		fade_speed29	0.007575758		// 1.1s
#define		fade_speed30	0.008333333		// 1s
#define		fade_speed31	0.008771930		// 0.95s
#define		fade_speed32	0.009259259		// 0.9s
#define		fade_speed33	0.009803922		// 0.85s
#define		fade_speed34	0.010416667		// 0.8s
#define		fade_speed35	0.011111111		// 0.75s
#define		fade_speed36	0.011904762		// 0.7s
#define		fade_speed37	0.012820513		// 0.65s
#define		fade_speed38	0.013888889		// 0.6s
#define		fade_speed39	0.015151515		// 0.55s
#define		fade_speed40	0.016666667		// 0.5s
#define		fade_speed41	0.018518519		// 0.45s
#define		fade_speed42	0.020833333		// 0.4s
#define		fade_speed43	0.023809524		// 0.35s
#define		fade_speed44	0.027777778		// 0.3s
#define		fade_speed45	0.033333333		// 0.25s
#define		fade_speed46	0.041666667		// 0.2s
#define		fade_speed47	0.055555556		// 0.15s
#define		fade_speed48	0.083333333		// 0.1s
#define		fade_speed49	0.016666667		// 0.05s
#define		fade_speed50	1.0				// 0s

// Steps that it will take for the current brightness
// to reach the desired brightness.
#define		fade_steps0		600
#define		fade_steps1		576
#define		fade_steps2		552
#define		fade_steps3		528
#define		fade_steps4		504
#define		fade_steps5		480
#define		fade_steps6		456
#define		fade_steps7		432
#define		fade_steps8		408
#define		fade_steps9		384
#define		fade_steps10	360
#define		fade_steps11	348
#define		fade_steps12	336
#define		fade_steps13	324
#define		fade_steps14	312
#define		fade_steps15	300
#define		fade_steps16	288
#define		fade_steps17	276
#define		fade_steps18	264
#define		fade_steps19	252
#define		fade_steps20	240
#define		fade_steps21	228
#define		fade_steps22	216
#define		fade_steps23	204
#define		fade_steps24	192
#define		fade_steps25	180
#define		fade_steps26	168
#define		fade_steps27	156
#define		fade_steps28	144
#define		fade_steps29	132
#define		fade_steps30	120
#define		fade_steps31	114
#define		fade_steps32	108
#define		fade_steps33	102
#define		fade_steps34	96
#define		fade_steps35	90
#define		fade_steps36	84
#define		fade_steps37	78
#define		fade_steps38	72
#define		fade_steps39	66
#define		fade_steps40	60
#define		fade_steps41	54
#define		fade_steps42	48
#define		fade_steps43	42
#define		fade_steps44	36
#define		fade_steps45	30
#define		fade_steps46	24
#define		fade_steps47	18
#define		fade_steps48	12
#define		fade_steps49	6
#define		fade_steps50	1


// Variables //

// Duty Cycle Variables. 
// This number is reset to a value between 1-99 at the end of every cycle (10ms)
// and the associated LED turned on. It is then counted down (0.1ms) and when the
// count hits 1, the associated LED turned off.
typedef struct RGB 
{
	unsigned char r:8;
	unsigned char g:8;
	unsigned char b:8;
};

struct RGB zone_brightness[13] = {0};
struct RGB zone_brightness_current[13] = {0};
struct RGB zone_brightness_target[13] = {0};
struct RGB zone_brightness_target_next[13] = {0};
struct RGB zone_brightness_target_old[13] = {0};
static unsigned char fade_speed = 0;

// Zone Pulse Width Counter.
// This number is reset at the end of every LED pulse.  It is then counted down (0.1ms)
// and when it hits 0, triggers a reloading of the Duty Cycle Variables, turns the
// associated LEDs on, and resets itself.
static unsigned char	brightness_count[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Frequency Variables.
// These variables govern the frequency the lights flash at.  They are used to load
// the high and low Timer0 registers.  
// Timer0 is Fosc(64MHz) / 4 / 8(prescale) = 2000000.
// Value = 2^16 - (2 000 000 / (Desired Frequency * 12))
static unsigned char	frequency_high = 0;		// 64702 = 200Hz.
static unsigned char 	frequency_low = 0;

// Duty Cycle Variables.
// These variables govern the duty cycle divisions of the lights. The Strobe is designed
// for 1% duty cycle increments.  These values are used to load the high and low
// Timer1 registers.
// Timer1 is Fosc(64Mhz) /4 / 8(prescale) = 2000000.
// Value = 2^16 - (2 000 000 / (Desired Frequency * 100))
static unsigned char	dutycycle_high = 0;
static unsigned char	dutycycle_low = 0;

// Manual Operation
// Zone selected for adjustment.
static unsigned char	zone_select = 0;
static unsigned char	zone_select_old = 0;


/*****************************************************************************************
 *                                   INTERRUPTS	     									 *
 *****************************************************************************************/

// Definitions //

// Timer that governs the frequency the LEDs flash at. Default 200Hz.
#define		frequency_timer			T0CONbits.TMR0ON	// Timer0 ON / OFF bit.
#define		frequency_timer_flag	INTCONbits.TMR0IF	// Timer0 Interrupt flag.

// Timer that controls each LEDs duty cycle. Default 200Hz / 100.
#define		dutycycle_timer			T1CONbits.TMR1ON	// Timer1 ON / OFF bit.
#define		dutycycle_timer_flag	PIR1bits.TMR1IF		// Timer1 Interrupt flag.

// Timer that controls when the adc is ready for another conversion.
#define		adc_timer				T2CONbits.TMR2ON	// Timer2 ON / OFF bit.
#define		adc_timer_flag			PIR1bits.TMR2IF		// Timer2 Interrupt flag.

// Timer to add delay between characters printed to the OLED screen.
#define		oled_timer				T3CONbits.TMR3ON	// Timer3 ON / OFF bit.
#define		oled_timer_flag			PIR2bits.TMR3IF		// Timer3 Interrupt flag.

// Timer that controls when the adc is ready for another conversion.
#define		blink_timer				T4CONbits.TMR4ON	// Timer4 ON / OFF bit.
#define		blink_timer_flag		PIR5bits.TMR4IF		// Timer4 Interrupt flag.

// Timer that controls when the buttons are ready to be checked.
#define		button_timer			T5CONbits.TMR5ON	// Timer5 ON / OFF bit.
#define		button_timer_flag		PIR5bits.TMR5IF		// Timer5 Interrupt flag.

// Timer that controls changing stages of the STROBE function.
#define		stage_timer				T6CONbits.TMR6ON	// Timer6 ON / OFF bit.
#define		stage_timer_flag		PIR5bits.TMR6IF		// Timer6 Interrupt flag.

// Timer that controls when the motion sensors are ready to be checked. Default 100ms.
#define		ms_timer				T7CONbits.TMR7ON	// Timer7 ON / OFF bit.
#define		ms_timer_flag			PIR5bits.TMR7IF		// Timer7 Interrupt flag.	

// Timer that controls the STROBE LIGHT function.
#define		strobelight_timer		T8CONbits.TMR8ON	// Timer8 ON / OFF bit.
#define		strobelight_timer_flag	PIR5bits.TMR8IF		// Timer8 Interrupt flag.

// Timer that controls the STROBE LIGHT function.
#define		load_timer				T10CONbits.TMR10ON	// Timer10 ON / OFF bit.
#define		load_timer_flag			PIR5bits.TMR10IF	// Timer10 Interrupt flag.	

// Variables //

#pragma idata INTERRUPTS
static unsigned char	frequency_trigger = 0;
static unsigned char	dutycycle_trigger = 0;

// Adds proper delay to the ms_timer. Default (5) 20ms >> 100ms.
static unsigned char	ms_timer_count = 5;

// Controls when the STROBE LIGHT turns on and off.
static unsigned char	strobelight_ready = 0;
static unsigned int	strobelight_count = 0;
static unsigned int	strobelight_time_off = 0;
static unsigned int	strobelight_time_on = 0;

// Controls the delay on the loading bar.
static unsigned char	load_ready = 0;
static unsigned int	load_count = 0;

/*****************************************************************************************
 *                                      OLED											 *
 *****************************************************************************************/

// Definitions //

// Process definitions that get passed into the strobe_oled().
#define		oled_menu			1
#define		oled_zone			2
#define		oled_run			3

// OLED communication bits.
#define		scs			PORTCbits.RC2	// Chip select bit. Active low.
#define		sck			PORTCbits.SCK1	// Clock. Clocks data low to high.
#define		sdi			PORTCbits.SDI1	// Data received from the OLED.
#define		sdo			PORTCbits.SDO1	// Data sent to the OLED.

// Custom Characters.
#define		oled_cursor			 	0x07	// Custom character 8.
#define		oled_cursor_address		0x78	// CGRAM location 1.

#define		oled_load1				0x02	// 1 line.
#define		oled_load2				0x03	// 2 lines.
#define		oled_load3				0x04	// 3 lines.
#define		oled_load4				0x05	// 4 lines.
#define		oled_load5				0x06	// 5 lines.

#define		oled_space				0x20	// Space character.


// Variables //

// Structure that stores a character 'byte'.  Each bit of the byte is addressed by 'b0..b7'.
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
typedef struct display_data
{
	unsigned char menu;
	unsigned char line;
	unsigned char position;
	unsigned char display[4][21];
	unsigned char buffer[4][21];
};

#pragma idata OLEDDATA

// RAM location for the OLED structure.
struct 	display_data oled = {0};

#pragma idata INTERRUPTS
// Bit for telling if the OLED is ready to be sent more data.
// 1 - OLED is ready for more data.
// 0 - OLED has not waited a sufficient time for more data.
static unsigned char oled_ready = 0;


/*****************************************************************************************
 *                                     Blink											 *
 *****************************************************************************************/

// Definitions //

// Process definitions that get passed into the strobe_blink().
#define		blink_init		1
#define		blink_run		2
#define		blink_deinit	3

// Delay definitions for ON/OFF time.
#define		blink_delay_on	120		// 120 * 4ms = 600ms.
#define		blink_delay_off	30		// 30 * 4ms = 150ms.


// Variables //

// Adds delay to the blink timer so that the frequency of the blinking can be adjusted.
static unsigned char blink_count = 0;

// Bit for telling if the blink is ready to switch.
static unsigned char blink_ready = 0;


/*****************************************************************************************
 *                                      ADC												 *
 *****************************************************************************************/

// Definitions //

// Process definitions that get passed into the strobe_adc().
#define		adc_single_init			1
#define		adc_dual_init			2
#define		adc_single_run			3
#define		adc_dual_run			4
#define		adc_single_deinit		7
#define		adc_dual_deinit			8

// This register controls which line is being looked at by the ADC unit.
// Change adc_select to equal adc_pot1 or adc_pot2 depending on which pot you want to
// measure.
#define		adc_select		ADCON0bits.CHS
#define		adc_pot1		0b00000
#define		adc_pot2		0b00001

// This register starts the ADC conversion.  If it is set, it is mid conversion and is
// not ready to start another. Setting it will start a conversion and the register
// will clear itself when it is finished.
#define		adc_start		ADCON0bits.DONE

// This register turns the ADC unit on and off.
#define		adc_on			ADCON0bits.ADON

// ADC Conversion Interrupt bits.
// These registers control the interrupt enable and interrupt flag.
#define		adc_flag		PIR1bits.ADIF
#define		adc_int			PIE1bits.ADIE

// This register contains the eight MSB of the ADC result.
#define		pot_level		ADRESH

// Delay between ADC checks. Frequency = adc_delay * 4ms. (default 100ms)
#define		adc_delay		1


// Variables //

// Bit for telling if the ADC is ready for another conversion.
// 1 - ADC is ready for another conversion.
// 0 - ADC has not waited a sufficient time for another conversion.
static unsigned char adc_ready = 0;

// Adds delay to the adc timer so that the frequency of adc conversions can
// be adjusted.
static unsigned char adc_count = 0;


/*****************************************************************************************
 *                                      MEMORY											 *
 *****************************************************************************************/

// Definitions //

// Process definitions that get passed into the strobe_mem().
#define		mem_save_init				1
#define		mem_save_run				2
#define		mem_manual_load_names		3
#define		mem_strobe_short_load_names 4
#define		mem_strobe_long_load_names 	5

// In line assembly instructions for writing and reading to the tables.
#define		table_write   				 _asm TBLWTPOSTINC _endasm   // Table write.

// Memory locations of specific save segments.

// Manual Save Locations //
// Slot 1
#define		manual1_config_add			0x11F00
#define		manual1_name_add			0x11F02
#define		manual1_red_add				0x11F10
#define		manual1_green_add			0x11F20
#define		manual1_blue_add			0x11F30

// Slot 2
#define		manual2_config_add			0x11F40
#define		manual2_name_add			0x11F42
#define		manual2_red_add				0x11F50
#define		manual2_green_add			0x11F60
#define		manual2_blue_add			0x11F70

// Slot 3
#define		manual3_config_add			0x11F80
#define		manual3_name_add			0x11F82
#define		manual3_red_add				0x11F90
#define		manual3_green_add			0x11FA0
#define		manual3_blue_add			0x11FB0

// Slot 4
#define		manual4_config_add			0x11FC0
#define		manual4_name_add			0x11FC2
#define		manual4_red_add				0x11FD0
#define		manual4_green_add			0x11FE0
#define		manual4_blue_add			0x11FF0

// Strobe Short Save Locations //
// Slot 1
#define		strobe_short1_config_add	0x12000
#define		strobe_short1_name_add		0x12010
#define		strobe_short1_red_add		0x12020
#define		strobe_short1_green_add		0x12030
#define		strobe_short1_blue_add		0x12040

// Slot 2
#define		strobe_short2_config_add	0x12800
#define		strobe_short2_name_add		0x12810
#define		strobe_short2_red_add		0x12820
#define		strobe_short2_green_add		0x12830
#define		strobe_short2_blue_add		0x12840

// Slot 3
#define		strobe_short3_config_add	0x13000
#define		strobe_short3_name_add		0x13010
#define		strobe_short3_red_add		0x13020
#define		strobe_short3_green_add		0x13030
#define		strobe_short3_blue_add		0x13040

// Slot 4
#define		strobe_short4_config_add	0x13800
#define		strobe_short4_name_add		0x13810
#define		strobe_short4_red_add		0x13820
#define		strobe_short4_green_add		0x13830
#define		strobe_short4_blue_add		0x13840

// Strobe Long Save Locations //
// Slot 1
#define		strobe_long1_config_add		0x14000
#define		strobe_long1_name_add		0x14010
#define		strobe_long1_red_add		0x14020
#define		strobe_long1_green_add		0x14030
#define		strobe_long1_blue_add		0x14040

// Slot 2
#define		strobe_long2_config_add		0x17000
#define		strobe_long2_name_add		0x17010
#define		strobe_long2_red_add		0x17020
#define		strobe_long2_green_add		0x17030
#define		strobe_long2_blue_add		0x17040

// Slot 3
#define		strobe_long3_config_add		0x1A000
#define		strobe_long3_name_add		0x1A010
#define		strobe_long3_red_add		0x1A020
#define		strobe_long3_green_add		0x1A030
#define		strobe_long3_blue_add		0x1A040

// Slot 4
#define		strobe_long4_config_add		0x1D000
#define		strobe_long4_name_add		0x1D010
#define		strobe_long4_red_add		0x1D020
#define		strobe_long4_green_add		0x1D030
#define		strobe_long4_blue_add		0x1D040

#pragma idata DATA1

// Variables
static unsigned char	config[2] = {0};
static unsigned char	name[16] = {0};
static unsigned char	current_letter = 0;


/*****************************************************************************************
 *                                      STAGE											 *
 *****************************************************************************************/

// Definitions //
#define stage_init			1
#define	stage_save_init		4
#define	stage_save_run		5
#define	stage_run			2
#define	stage_deinit		3

// Used in the stage data array for pointing to specific bytes.
#define	total_stages		0
#define	hold_time1h			44
#define hold_time1l			45
#define hold_time2h			92
#define hold_time2l			93
#define	fade_time1			60
#define	fade_time2			108

#define	red1				32
#define	green1				48
#define blue1				64
#define red2				80
#define green2				96
#define blue2				112

// Variables

#pragma idata INTERRUPTS

// Adds delay to the stage timer so that the frequency of the stage changes can be adjusted.
static unsigned int stage_count = 0;

// Bit for telling if the stage is ready to change.
static unsigned char stage_ready = 0;

#pragma idata LIGHTS

typedef struct FADE
{
	unsigned float	r;
	unsigned float	g;
	unsigned float	b;
};

// Registers that hold the fade step size and the current brightness at the current step.
struct FADE	zone_brightness_fade_stepsize[13] = {0};
struct FADE zone_brightness_fade_stepsum[13] = {0};

// Register for keeping track of the current step.
static unsigned int stage_fade_steps = 0;

// Register for keeping track of the current stage being saved.
static unsigned char   stage_save_count = 0;

// Register for keeping track of the current slot being saved. (1-4 short, 5-8 long)
static unsigned char   stage_save_slot = 0;

static unsigned int	adc_hold_time = 0;
static unsigned char	adc_fade_time = 0;

#pragma idata DATA1

/*****************************************************************************************
 *                                      PRINTING										 *
 *****************************************************************************************/

// Used in the print_delay as process for different variables being controlled by the dial.
#define		timeout_delay		1
#define		hold_time			2
#define		fade_time			3
