//*********************************************************************
//* Custom user defined variables for the registers in an PIC18F87K90 *
//*																	  *
//* Written by Zachary Lang                                           *
//* January 12, 2015                                               	  *
//*********************************************************************


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

// Variables //

// Keeps track of when the buttons are ready for another check. 1 >> 20ms, 25 >> 500ms.
#pragma idata INTERRUPTS
unsigned char	button_wait = 0;

	
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
unsigned char	ms_ready = 0;

// Counting veriable used by the timer.
unsigned char	ms_count = 0;

#pragma idata LIGHTS
// Adjustable time out delay setting for the motion sensors.  This value is changed by the user.
unsigned int	zone_timeout_delay = 100;
unsigned int	zone_timeout_delay_old = 0;

// Adjacent Zone Brightness.
// 100 being maximum brightness and 0 being off.
unsigned char	adjacent_brightness	= 20;
unsigned char	adjacent2_brightness = 5;
unsigned char	adjacent3_brightness = 0;
unsigned char	adjacent_brightness_old	= 0;
unsigned char	adjacent2_brightness_old = 0;
unsigned char	adjacent3_brightness_old = 0;


/*****************************************************************************************
 *                                     LEDS      										 *
 *****************************************************************************************/

// Definitions //

// Process definitions that get passed into the strobe_lights().

#define		led_ms_init				1
#define		led_manual_init			2
#define		led_run					3
#define		led_ms_deinit			4
#define		led_manual_deinit		5

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

// Fade Speeds.
#define		fade_fast		1
#define		fade_medium		3
#define		fade_slow		5

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
struct RGB zone_brightness_buffer[13] = {0};
struct RGB zone_brightness_target[13] = {0};
struct RGB zone_brightness_target_old[13] = {0};
unsigned char fade_speed;

// Zone Pulse Width Counter.
// This number is reset at the end of every LED pulse.  It is then counted down (0.1ms)
// and when it hits 0, triggers a reloading of the Duty Cycle Variables, turns the
// associated LEDs on, and resets itself.
unsigned char	brightness_count[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Frequency Variables.
// These variables govern the frequency the lights flash at.  They are used to load
// the high and low Timer0 registers.  
// Timer0 is Fosc(64MHz) / 4 / 8(prescale) = 2000000.
// Value = 2^16 - (2 000 000 / (Desired Frequency * 12))
unsigned char	frequency_high;		// 64702 = 200Hz.
unsigned char 	frequency_low;

// Duty Cycle Variables.
// These variables govern the duty cycle divisions of the lights. The Strobe is designed
// for 1% duty cycle increments.  These values are used to load the high and low
// Timer1 registers.
// Timer1 is Fosc(64Mhz) /4 / 8(prescale) = 2000000.
// Value = 2^16 - (2 000 000 / (Desired Frequency * 100))
unsigned char	dutycycle_high;
unsigned char	dutycycle_low;

// Manual Operation
// Zone selected for adjustment.
unsigned char	manual_zone_select = 0;
unsigned char	manual_zone_select_old = 0;


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

// Timer that controls when the motion sensors are ready to be checked. Default 100ms.
#define		ms_timer				T7CONbits.TMR7ON	// Timer7 ON / OFF bit.
#define		ms_timer_flag			PIR5bits.TMR7IF		// Timer7 Interrupt flag.		

// Variables //

#pragma idata INTERRUPTS
unsigned char	frequency_trigger = 0;
unsigned char	dutycycle_trigger = 0;

// Adds proper delay to the ms_timer. Default (5) 20ms >> 100ms.
unsigned char	ms_timer_count = 5;

/*****************************************************************************************
 *                                      OLED											 *
 *****************************************************************************************/

// Definitions //

// Process definitions that get passed into the strobe_oled().
#define		oled_menu			1
#define		oled_ms_adc			2
#define		oled_manual_zone	3
#define		oled_manual_color	4
#define		oled_run			5

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
	char display[4][21];
	char buffer[4][21];
};

#pragma idata OLEDDATA

// RAM location for the OLED structure.
struct 	display_data oled = {0};

#pragma idata INTERRUPTS
// Bit for telling if the OLED is ready to be sent more data.
// 1 - OLED is ready for more data.
// 0 - OLED has not waited a sufficient time for more data.
unsigned char oled_ready = 0;


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
#define		blink_delay_off	60		// 60 * 4ms = 300ms.


// Variables //

// Adds delay to the blink timer so that the frequency of the blinking can be adjusted.
unsigned char blink_count = 0;

// Bit for telling if the blink is ready to switch.
unsigned char blink_ready = 0;


/*****************************************************************************************
 *                                      ADC												 *
 *****************************************************************************************/

// Definitions //

// Process definitions that get passed into the strobe_adc().
#define		adc_ms_init		1
#define		adc_manual_init	2
#define		adc_strobe_init	3
#define		adc_ms_run				4
#define		adc_manual_run			5
#define		adc_strobe_run			6
#define		adc_ms_deinit		7
#define		adc_manual_deinit	8
#define		adc_strobe_deinit 9


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
unsigned char adc_ready = 0;

// Adds delay to the adc timer so that the frequency of adc conversions can
// be adjusted.
unsigned char adc_count = 0;

/*
// This bit triggers after a conversion has finished and is cleared when
// the converted value has been received and used.
unsigned char adc_conversion_done = 0;

// Variable that stores the percentage of Dial 1 and 2 in 1% increments.
// 0 - 0% >>>> 100 - 100%
unsigned char dial[2] = {0};

// Bit that flags the color being adjusted in manual mode. The pot will only be affecting
// the color when its corresponding bit is enabled.
unsigned char manual_change_red = 0;
unsigned char manual_change_green = 0;
unsigned char manual_change_blue = 0;

// Register that keeps track of the brightness of each color selected in manual mode.
// These values are only changed when the user selects color brightness in the menu and
// then hits SAVE. Those temporary values are then written here. If the user cancels, these
// values stay the same.
unsigned char manual_brightness_red = 0;
unsigned char manual_brightness_green = 0;
unsigned char manual_brightness_blue = 0;

// Register that keeps track of the temporary brightness of each color selected by the pots.  This
// value is only changed when the corresponding manual_change_**** is enabled.  If the user saves
// these values they are written into the saved locations manual_brightness_****.
unsigned char manual_brightness_red_temp = 0;
unsigned char manual_brightness_green_temp = 0;
unsigned char manual_brightness_blue_temp = 0;
*/

/*
// Test Declaration of Variables.
//#pragma idata OLEDDATA
struct 	display_data oled = {0};

//#pragma idata LIGHTS
struct RGB zone_brightness[13] = {0};
struct RGB zone_brightness_buffer[13] = {0};
struct RGB zone_brightness_target[13] = {0};
unsigned char fade_speed;

// Zone Pulse Width Counter.
// This number is reset at the end of every LED pulse.  It is then counted down (0.1ms)
// and when it hits 0, triggers a reloading of the Duty Cycle Variables, turns the
// associated LEDs on, and resets itself.
unsigned char	brightness_count[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Frequency Variables.
// These variables govern the frequency the lights flash at.  They are used to load
// the high and low Timer0 registers.  
// Timer0 is Fosc(64MHz) / 4 / 8(prescale) = 2000000.
// Value = 2^16 - (2 000 000 / (Desired Frequency * 12))
unsigned char	frequency_high;		// 64702 = 200Hz.
unsigned char 	frequency_low;

// Duty Cycle Variables.
// These variables govern the duty cycle divisions of the lights. The Strobe is designed
// for 1% duty cycle increments.  These values are used to load the high and low
// Timer1 registers.
// Timer1 is Fosc(64Mhz) /4 / 8(prescale) = 2000000.
// Value = 2^16 - (2 000 000 / (Desired Frequency * 100))
unsigned char	dutycycle_high;
unsigned char	dutycycle_low;

// Adjacent Zone Brightness.
// 100 being maximum brightness and 0 being off.
unsigned char	adjacent_brightness	= 20;
unsigned char	adjacent2_brightness = 5;
unsigned char	adjacent3_brightness = 0;
unsigned char	adjacent_brightness_old	= 0;
unsigned char	adjacent2_brightness_old = 0;
unsigned char	adjacent3_brightness_old = 0;

//#pragma idata FLAGS
// Keeps track of when the buttons are ready for another check. 1 >> 20ms, 25 >> 500ms.
unsigned char	button_wait = 0;

// Bit for telling if the ADC is ready for another conversion.
// 1 - ADC is ready for another conversion.
// 0 - ADC has not waited a sufficient time for another conversion.
unsigned char adc_ready = 0;

// Adds delay to the adc timer so that the frequency of adc conversions can
// be adjusted.
unsigned char adc_count = 0;

// Adds delay to the blink timer so that the frequency of the blinking can be adjusted.
unsigned char blink_count = 0;

// Bit for telling if the blink is ready to switch.
unsigned char blink_ready = 0;

// Bit for telling if the OLED is ready to be sent more data.
// 1 - OLED is ready for more data.
// 0 - OLED has not waited a sufficient time for more data.
unsigned char oled_ready = 0;

unsigned char	frequency_trigger;
unsigned char	dutycycle_trigger;

// Adds proper delay to the ms_timer. Default (5) 20ms >> 100ms.
unsigned char	ms_timer_count = 5;

// Bit for telling if the motion sensors are ready to be checked again. Default 100ms.
// 1 - Motion sensors are ready to be checked.
// 0 - Motion sensors have not waited a sufficient time to be checked.
unsigned char	ms_ready = 0;

// Counting veriable used by the timer.
unsigned char	ms_count;

// Adjustable time out delay setting for the motion sensors.  This value is changed by the user.
unsigned int	zone_timeout_delay = 100;
unsigned int	zone_timeout_delay_old = 0;

//#pragma udata DATA1
*/

#pragma idata data1
