
// My Prototypes //

// Initializations //
void osc_init(void);
void int_init(void);
void port_init(void);
void spi_init(void);
void oled_init(void);
void adc_init(void);

// Welcome //
void strobe_welcome(void);
void welcome_load(unsigned char *percent);
void welcome_message(void);

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
void oled_load_zone(void);
void oled_send_buffer(void);
void oled_send_command(unsigned int rs, unsigned int rw, unsigned char command);
void oled_print(unsigned char char_data);

// Lights //
void strobe_lights(static unsigned char lights_process);
void lights_frequency(void);
void lights_frequency_stage(unsigned char reset_zone);
void lights_dutycycle(void);
void lights_stage(static unsigned char stage_process, static unsigned char stage_slot);
void lights_strobelight(void);

// Motion Sensors //
void strobe_motionsensors(unsigned char ms_process);

// ADC //
void strobe_adc(unsigned char adc_process);

// Blink //
void strobe_blink(unsigned char blink_process);
void blink(unsigned char force_on);

// Print Functions //
void print_progress_bar(unsigned char row, unsigned char start_position, unsigned char percent);
void print_delay(unsigned char percent, unsigned char delay_process);
void print_ms_lightspread(unsigned char percent);
void print_strobe_fadetime(unsigned char percent);

// Memory //
void strobe_mem(unsigned char mem_process, unsigned char slot, static unsigned char *trigger);
void mem_manual_save(unsigned char slot);
void mem_manual_load_lights(unsigned char slot);
void mem_print_name(unsigned long mem_location, unsigned char line);
void mem_erase(unsigned long mem_add_start, unsigned long mem_add_stop);
void mem_read(unsigned long mem_add_start, unsigned char *data, unsigned char length);
void mem_write(unsigned long mem_add_start, unsigned char *data, unsigned char length);
void mem_write_cmd(void);


