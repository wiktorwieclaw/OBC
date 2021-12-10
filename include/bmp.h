#include <Arduino.h>
//#include <math.h>
#include <SPI.h>
#include <SD.h>
#include "BMP280.h"
#include "Wire.h"

#ifndef BMP
#define BMP

#define STATUS_GREEN_PIN A2
#define STATUS_RED_PIN A1
#define HOT_SWAP_BUTTON A3
#define P0 1013.25


void _init();
void measurments();

#endif