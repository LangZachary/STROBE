
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
	ANCON0 = 0b00000000;
	ANCON1 = 0b00000000;
	ANCON2 = 0b00000000;
	PORTA = 0b00000000;
	PORTB = 0b00000100;
	PORTC = 0b00000100;	  // x, x, x, x, scs, x, x
	PORTD =	0b00000000;
	PORTE = 0b00000000;
	TRISA = 0b00111111;   // x, x, ms3, ms4, ms1, ms2, Pot2, Pot1
	TRISB = 0b00111110;	  // x, x, down, up, enter, menu, x, z12b 
	TRISC = 0b00010011;	  // x, x, sdo, sdi, sck, scs, ms5, ms6
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
	INTCONbits.GIE = 1;		// Enable all interrupts.
	INTCONbits.GIEL = 1;	// Enable low priority interrupts.
	RCONbits.IPEN = 1;		// Enable priority levels on interrupts.

	// OLED Timer3 //
	T3GCONbits.TMR3GE = 0;	// Disable Gate Control.
	T3CONbits.TMR3CS = 0b00;// Fosc / 4.
	T3CONbits.T3CKPS = 0b11;// 1:8 Prescale.
	T3CONbits.SOSCEN = 0;	// SOSC Disabled.
	T3CONbits.RD16 = 1;		// 16-bit write to Timer Delay.
	PIE2bits.TMR3IE = 1;	// Enable Interrupt.
	IPR2bits.TMR3IP = 0;	// Low priority.
	oled_timer_flag = 0;	// Reset Interrupt Flag.
	oled_timer = 0;			// Keep Timer 3 Off.
	
	// Button Timer5 //
	T5GCONbits.TMR5GE = 0;	// Disable Gate Control.
	T5CONbits.TMR5CS = 0b00;// Fosc/4.
	T5CONbits.T5CKPS = 0b11;// 1:8 Prescale.
	T5CONbits.SOSCEN = 0;	// SOSC Disabled.
	T5CONbits.RD16 = 1;		// 16-bit write.
	PIE5bits.TMR5IE = 1;	// Enable Interrupt.
	IPR5bits.TMR5IP = 0;	// Low priority.
	button_timer_flag = 0;	// Reset Interrupt Flag.
	TMR5H = 0x63;			// Set for 20ms delay.
	TMR5L = 0xC0;
	button_timer = 1;		// Turn Timer5 on.



//	OpenTimer0( TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_PS_1_256);
//	WriteTimer0(665411);		// 625 cycles = 10ms Timer. 64911 = 10ms.
	
//	INTCONbits.TMR0IF = 0;  // Clear Timer0 interrupt flag.
//	INTCON2bits.TMR0IP = 1;	// Set Timer0 priority high.

	
/*	TMR0H = 0xFF;			// 5000 cycles - 60536.
	TMR0L = 0xFF;			// 10ms.
	T0CON = 0b00000001;		// Timer0 off, 16bit, Intern clock, Non-inv, Pre-Scale 1:4.
	INTCONbits.TMR0IF = 0;  // Clear Timer0 interrupt flag.
	INTCONbits.TMR0IE = 1;  // Enable Timer0 interrupt.
	INTCON2bits.TMR0IP = 1; // Change Timer0 priority high.

	TMR1H = 255;			// 200 cycles - 65336
	TMR1L = 56;				// 100us.
	T1CON = 0b00000000;		// Timer1 off, 1:1, Intern clock.
	T1GCON = 0b00000000;	// Disable Timer1 gate.
	PIR1bits.TMR1IF = 0;	// Clear Timer1 interrupt flag.
	PIE1bits.TMR1IE = 1;	// Enable Timer1 interrupt.
	IPR1bits.TMR1IP = 0;	// Change Timer1 priority low.


	RCONbits.IPEN = 1;		// Enable low priority interupts.
	INTCON = 0b11100000;	// Global enable, Timer0 enable, Int0 + RB1 disable, Clear flags.
	T0CONbits.TMR0ON = 1;	// Turn Timer0 counter on.
	T1CONbits.TMR1ON = 1;	// Turn Timer1 counter on.
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
	oled_timer_delayh = 0xF0;
	oled_timer_delayl = 0x60;

	// Start Timer for OLED to be ready to receive more data.
	oled_timer = 1;

	// Set the menu to main menu.
	oled.menu = select_menu1;

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
}




