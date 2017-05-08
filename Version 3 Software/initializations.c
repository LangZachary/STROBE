
// Initializations //

// This code controls the initilization sequences for the Ports,
// Timers and Interrupts, Serial Communications, Buttons, ADC

// Oscillator Initialize //
void osc_init(void)
{
	OSCCONbits.IDLEN = 0;		// Micro sleeps on sleep command.
	OSCCONbits.IRCF = 0b111;	// 16MHz.
	OSCCONbits.SCS = 0b00;		// Primary Oscillator used.
	OSCTUNEbits.INTSRC = 0b0;	// 31 kHz derived from 16Mhz / 512.
	OSCTUNEbits.PLLEN = 1;		// 4xPLL enabled.
	OSCTUNEbits.TUN = 0b000010;	// Oscillator tuned for 16MHz.
}

// Port Initialize //
void port_init(void)
{
	ANCON0 = 0b00000011;  // x, x, x, x, x, x, Pot2, Pot1
	ANCON1 = 0b00000000;
	ANCON2 = 0b00000000;
	PORTA = 0b00000000;
	PORTB = 0b00000100;
	PORTC = 0b00000100;	  // x, x, x, x, scs, x, x
	PORTD =	0b00000000;
	PORTE = 0b00000000;
	PORTF = 0b00000000;
	PORTG = 0b00000000;
	PORTH = 0b00000000;
	PORTJ = 0b00000000;
	TRISA = 0b00111111;   // x, x, ms3, ms4, ms1, ms2, Pot2, Pot1
	TRISB = 0b00111110;	  // x, x, down, up, enter, menu, x, z12b 
	TRISC = 0b11010011;	  // ms8, ms7, sdo, sdi, sck, scs, ms5, ms6
	TRISD = 0b00000000;	  // z11r, z10b, z10g, z10r, z9b, z9g, z9r, z8b
	TRISE = 0b00000000;	  // z8g, z8r, z7b, z7g, z7r, x, z5g, z5r
	TRISF = 0b00000000;	  // z3g, z3r, z2b, z2g, z2r, z1b, x, x
	TRISG = 0b00000000;	  // x, x, x, x, z3b, z4r, z4g, z4b
	TRISH = 0b00000000;	  // z1g, z1r, x, x, z5b, z6r, z6g, z6b
	TRISJ = 0b11110000;	  // ms12, ms11, ms10, ms9, z12g, z12r, z11b, z11g

	// Enable pull-ups
	INTCON2bits.NOT_RBPU = 1;
}

// Interrupt Initialize //
void int_init(void)
{
	INTCONbits.GIE = 1;			// Enable all interrupts.
	INTCONbits.GIEL = 1;		// Enable low priority interrupts.
	RCONbits.IPEN = 1;			// Enable priority levels on interrupts.

	// LED FREQUENCY Timer0 - 100us - High Priority //
	T0CONbits.T0CS = 0;			// Fosc/4.
	T0CONbits.T0SE = 0;			// Non-inverted.
	T0CONbits.PSA = 0;			// Prescaler on.
	T0CONbits.T0PS = 0b010;		// 1:8 Prescale.
	T0CONbits.T08BIT = 0;		// 16-bit.
	INTCONbits.TMR0IE = 1;		// Enable Interrupt.
	INTCON2bits.TMR0IP = 0;		// High priority.
	TMR0H = frequency_high;		// 64702 = 200Hz.
	TMR0L = frequency_low;
	frequency_timer_flag = 0;	// Reset Interrupt Flag.
	frequency_timer = 0;		// Turn Timer0 off for debugging.
	frequency_trigger = 0;

	// LED DUTY CYCLE Timer1 - 12us - High Priority //
	T1GCONbits.TMR1GE = 0;		// Disable Gate Control.
	T1CONbits.TMR1CS = 0b00;	// Fosc / 4.
	T1CONbits.T1CKPS = 0b11;	// 1:8 Prescale.
	T1CONbits.SOSCEN = 0;		// SOSC Disabled.
	T1CONbits.RD16 = 1;			// 16-bit write to Timer Delay.
	PIE1bits.TMR1IE = 1;		// Enable Interrupt.
	IPR1bits.TMR1IP = 0;		// High priority.
	TMR1H = 0xFF;				// Set for 12us. (24 cycles)
	TMR1L = 0xA0;
	dutycycle_timer_flag = 0;	// Reset Interrupt Flag.
	dutycycle_timer = 0;		// Turn Timer1 off for debugging.
	dutycycle_trigger = 0;

	// ADC Timer2 - 4ms - Low Priority //
	T2CONbits.T2OUTPS = 0b1111;	// 1:16 Postscale.
	T2CONbits.T2CKPS = 0b11;	// 1:16 Prescale.
	PIE1bits.TMR2IE = 1;		// Enable Interrupt.
	IPR1bits.TMR2IP = 0;		// Low priority.
	PR2 = 0xFA;					// 4ms interrupt.
	adc_timer_flag = 0;			// Reset Interrupt Flag.
	adc_timer = 0;				// Turn Timer2 Off.

	// OLED Timer3 - Low Priority //
	T3GCONbits.TMR3GE = 0;		// Disable Gate Control.
	T3CONbits.TMR3CS = 0b00;	// Fosc / 4.
	T3CONbits.T3CKPS = 0b11;	// 1:8 Prescale.
	T3CONbits.SOSCEN = 0;		// SOSC Disabled.
	T3CONbits.RD16 = 1;			// 16-bit write to Timer Delay.
	PIE2bits.TMR3IE = 1;		// Enable Interrupt.
	IPR2bits.TMR3IP = 0;		// Low priority.
	oled_timer_flag = 0;		// Reset Interrupt Flag.
	oled_timer = 0;				// Keep Timer 3 Off.
	
	// Button Timer5 - 20ms - Low Priority //
	T5GCONbits.TMR5GE = 0;		// Disable Gate Control.
	T5CONbits.TMR5CS = 0b00;	// Fosc/4.
	T5CONbits.T5CKPS = 0b11;	// 1:8 Prescale.
	T5CONbits.SOSCEN = 0;		// SOSC Disabled.
	T5CONbits.RD16 = 1;			// 16-bit write.
	PIE5bits.TMR5IE = 1;		// Enable Interrupt.
	IPR5bits.TMR5IP = 0;		// Low priority.
	button_timer_flag = 0;		// Reset Interrupt Flag.
	TMR5H = 0x63;				// Set for 20ms delay.
	TMR5L = 0xC0;
	button_timer = 1;			// Turn Timer5 on.

	// Motion Sensors Timer7 - 20ms - Low Priority //
	T7GCONbits.TMR7GE = 0;		// Disable Gate Control.
	T7CONbits.TMR7CS = 0b00;	// Fosc/4.
	T7CONbits.T7CKPS = 0b11;	// 1:8 Prescale.
	T7CONbits.SOSCEN = 0;		// SOSC Disabled.
	T7CONbits.RD16 = 1;			// 16-bit write.
	PIE5bits.TMR7IE = 1;		// Enable Interrupt.
	IPR5bits.TMR7IP = 0;		// Low priority.
	ms_timer_flag = 0;			// Reset Interrupt Flag.
	TMR7H = 0x63;				// Set for 20ms delay.
	TMR7L = 0xC0;
	ms_timer = 0;				// Turn Timer7 off.
/*
	// ADC Conversion Interrupt - Low Priority //
	IPR1bits.ADIP = 0;			// Low priority.
	adc_flag = 0;				// Turn the ADC flag off.
	adc_int = 1;				// Turn the ADC interrupt on.
*/
}

// SPI Initialize //
void spi_init(void)
{

	SSP1STATbits.SMP = 1;		// Input sampled at the end of data output time.
	SSP1STATbits.CKE = 0;		// Transmit occurs on transition from idle to active clock state.
	SSP1CON1bits.SSPEN = 0;		// Enables serial port and configures SCK1, SDO1, SDI1 and nSS1 as serial pins.
	SSP1CON1bits.CKP = 1;		// Idle state for clock is high level.
	SSP1CON1bits.SSPM = 0b0010;	// SPI Master Mode: Clock = FOSC / 64 = 1MHz.

}

// OLED Initialize //
void oled_init(void)
{
	// Set the OLED timer to wait 2ms for power stabilization.
	// OLED not ready for more data.
	oled_ready = 0;	

	// If the command is a reset, initiate a high (2ms) delay.
	TMR3H = 0xF0;
	TMR3L = 0x60;

	// Start Timer for OLED to be ready to receive more data.
	oled_timer = 1;

	// Set the menu to the welcome screen.
	oled.menu = welcome_screen1;

	// Save the welcome screen to the buffer.
	strobe_oled(load_menu, 0, 0);

	// Clear the oled.display.
  	strcpypgm2ram(oled.display[0], "                    ");
  	strcpypgm2ram(oled.display[1], "                    ");
  	strcpypgm2ram(oled.display[2], "                    ");
  	strcpypgm2ram(oled.display[3], "                    ");

	// Point to the first location.
	oled.line = 0;
	oled.position = 0;

	// Function Set: Data is 8-bit, Western characters.
	while(!oled_ready);
	oled_send_command(0, 0, 0x38);
	
	// Display OFF: No cursors, no blinking cursors.
	while(!oled_ready);
	oled_send_command(0, 0, 0x08);

	// Display Clear:
	while(!oled_ready);
	oled_send_command(0, 0, 0x01);

	// Entry Mode Set: Auto-increment right, no shift.
	while(!oled_ready);
	oled_send_command(0, 0, 0x06);

	// Entry Mode Set: Auto-increment right, no shift.
	while(!oled_ready);
	oled_send_command(0, 0, 0x06);

	// Home:
	while(!oled_ready);
	oled_send_command(0, 0, 0x02);

	// Display On:
	while(!oled_ready);
	oled_send_command(0, 0, 0x0C);

	// Create Custom Cursor
	oled_create_custom_cursor();

	// Create Custom Load Bar
	oled_create_custom_load();

}

// A2D Initialize //
void adc_init(void)
{
	ADCON1bits.VCFG = 0b00;		// Use AVdd for voltage reference.
	ADCON1bits.VNCFG = 0;		// Use AVss for ground reference.
	ADCON1bits.CHSN = 0b000;	// Use AVss for ground reference.
	ADCON2bits.ADFM = 0;		// Left justified, only using 8 MSBs.
	ADCON2bits.ACQT = 0b010;	// 4 Tad, 4us.
	ADCON2bits.ADCS = 0b110;	// Fosc / 64 = 1Mhz = 1us.
	adc_select = adc_pot1;  	// Start with the first pot.

	adc_on = 0;					// Turn the adc off.

//	WDTCONbits.REGSLP = 0;		// Regulator stays in normal node when sleep.
//	WDTCONbits.ULPEN = 0;		// Ultra-Low Power Wake-up is disabled.
//	WDTCONbits.SRETEN = 0;		// Regulator controlled by REGSLP in sleep.
}





