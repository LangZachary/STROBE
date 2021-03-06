# MPLAB IDE generated this makefile for use with GNU make.
# Project: STROBE.mcp
# Date: Fri Apr 17 20:30:15 2015

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

STROBE.cof : STROBE.o
	$(LD) /p18F87K90 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.46\lib" /k"C:\Users\Zak\Google Drive\Sask Polytech\Year 2 - Semester 2\STROBE" "STROBE.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /m"STROBE.map" /w /o"STROBE.cof"

STROBE.o : STROBE.c memory.h my_definitions.h my_prototypes.h menus.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/string.h STROBE.c initializations.c interrupts.c oled.c buttons.c lights.c motionsensors.c adc.c blink.c dials.c mem.c p18f87k90.h micro_setup.h dials.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.46/h/stddef.h
	$(CC) -p=18F87K90 /i"C:\Program Files (x86)\Microchip\mplabc18\v3.46\h" "STROBE.c" -fo="STROBE.o" -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "STROBE.o" "STROBE.cof" "STROBE.hex" "STROBE.map"

