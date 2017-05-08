
// My Prototypes //

// Initializations //
void osc_init(void);
void int_init(void);
void port_init(void);
void spi_init(void);
void oled_init(void);
void adc_init(void);

// Interrupts //
void high_interrupt_routine(void);
void low_interrupt_routine(void);

// Buttons //
void strobe_buttons(void);
unsigned char buttons_check(void);
void buttons_action(static unsigned char *trigger);

// OLED //
void strobe_oled(void);
void oled_load_buffer(void);
void oled_send_buffer(void);
void oled_send_command(unsigned int rs, unsigned int rw, unsigned char command);
void oled_print(unsigned char char_data);

// Lights //
void strobe_lights(void);
void lights_frequency(void);
void lights_dutycycle(void);

// Motion Sensors //
void strobe_motionsensors(void);

// ADC //
void strobe_adc(void);

