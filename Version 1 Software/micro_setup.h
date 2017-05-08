//************************************************************************************************
//Configuration Bits Set in code
//You find the definitions in MPlab only
//Help -> PIC18 Config Settings -> PIC18F45K22
//************************************************************************************************
#pragma config RETEN = OFF		//VREG Sleep Disabled - Controlled by SRETEN bit.
#pragma config INTOSCSEL = LOW 	//LF-INTOSC in Low-power mode during Sleep.
#pragma config SOSCSEL = HIGH	// High Power SOSC circuit selected.
#pragma config XINST = OFF		//Extended Instruction set disabled.
#pragma config FOSC = INTIO1	//Internal oscillator block, CLKOUT function on RA6, port function on RA7  
#pragma config PLLCFG = ON		//Oscillator not multiplied by 4, controlls external clocks only (not internal)  
#pragma config FCMEN = OFF 		//Fail-Safe Clock Monitor disabled  
#pragma config IESO = OFF		//Oscillator Switchover mode disabled  
#pragma config PWRTEN = OFF		//Power up timer disabled  
#pragma config BOREN = SBORDIS 	//Brown-out Reset disabled in hardware only   
#pragma config BORV = 2			//VBOR set to 2.0 V nominal  
#pragma config BORPWR = ZPBORMV //Zero Power Brown-out reset
#pragma config WDTEN = OFF 		//Watch dog timer is always disabled. SWDTEN has no effect. 
#pragma config RTCOSC = SOSCREF	//RTCC uses SOSC.
#pragma config CCP2MX = PORTBE 	//CCP2 input/output is multiplexed with RB3.
#pragma config ECCPMX = PORTH	//Enhanced CCP1/3 muxed with RH7/RH6/RH5/RH4.
#pragma config MSSPMSK = MSK7	//7 Bit address masking mode.   
#pragma config MCLRE = ON	 	//MCLR pin enabled, RE3 input pin disabled  
#pragma config STVREN = OFF		//Stack full/underflow will not cause Reset.
#pragma config BBSIZ = BB2K		//2K word Boot Block size.    
#pragma config DEBUG = ON		//Background debugging on RB7 & RB6
#pragma config CP0 = OFF		//BLOCK 0 NOT CODE PROTECTED
#pragma config CP1 = OFF		//BLOCK 1 NOT CODE PROTECTED
#pragma config CP2 = OFF		//BLOCK 2 NOT CODE PROTECTED
#pragma config CP3 = OFF		//BLOCK 3 NOT CODE PROTECTED
#pragma config CPB = OFF		//BOOT BLOCK NOT CODE PROTECTED
#pragma config CPD = OFF		//DATA EEPROM NOT CODE PROTECTED
#pragma config WRT0 = OFF		//BLOCK 0 NOT WRITE PROTECTED
#pragma config WRT1 = OFF		//BLOCK 1 NOT WRITE PROTECTED
#pragma config WRT2 = OFF		//BLOCK 2 NOT WRITE PROTECTED
#pragma config WRT3 = OFF		//BLOCK 3 NOT WRITE PROTECTED
#pragma config WRTB = OFF		//BOOT BLOCK NOT WRITE PROTECTED
#pragma config WRTC = OFF		//CONFIGURATION REGISTER NOT WRITE PROTECTED
#pragma config WRTD = OFF		//DATA EEPROM NOT WRITE PROTECTED
//************************************************************************************************//

