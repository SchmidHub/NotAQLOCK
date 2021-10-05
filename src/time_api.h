#ifndef TIME_API_H
#define TIME_API_H

#include <Arduino.h>

// Sends http get request and returns payload 
String httpGETRequest(const char*);
// Calculates time using an api call
void get_time_from_api();

#endif