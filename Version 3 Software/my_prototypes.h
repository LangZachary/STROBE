
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
void strobe_oled(unsigned char oled_process, unsigned char dial1, unsigned char dial2);
void oled_move_cursor(void);
void oled_create_custom_cursor(void);
void oled_create_custom_load(void);
void oled_load_menu(void);
void oled_load_adc(unsigned char dial1, unsigned char dial2);
void oled_send_buffer(void);
void oled_send_command(unsigned int rs, unsigned int rw, unsigned char command);
void oled_print(unsigned char char_data);

// Lights //
void strobe_lights(unsigned char lights_process);
void lights_frequency(void);
void lights_dutycycle(void);

// Motion Sensors //
void strobe_motionsensors(unsigned char ms_process);

// ADC //
void strobe_adc(unsigned char adc_process);

