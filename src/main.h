#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <Arduino.h>

// Globals
extern int8_t hours;
extern int8_t minutes;
extern const char* ssid;
extern const char* pass;


// Not used at the moment
void myTimerEvent();
// Fancy startup sequence
void led_startup();
// Copies the content of the write_idx array to the active_idx array
void copy_write_idx_to_active_idx();

/*
// Sends http get request and returns payload 
String httpGETRequest(const char*);
// Calculates time using an api call
void get_time_from_api();
*/

// Fills write_idx_array with -1
void clear_write_idx_array();
// Initializes an array containing all letters, their x and y coordinates and their status -- atm not really used
void init_letter_array();
// Adds one or multiple idx to write_idx_array
void add_to_write_idx(int8_t start, int8_t amount);
// Calculates which leds should be lit depending on the current time
void calculate_next_leds();
// Lights all leds stored in write_idx array if time, brightness or color changed
void show_leds();
// Init procedure 
void setup();
// Running procedure
void loop();


#endif