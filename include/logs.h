#include <Arduino.h>
//#include <math.h>
#include <SPI.h>
#include <SD.h>
#include "BMP280.h"
#include "Wire.h"
#include "bmp.h"


#ifndef LOGS
#define LOGS

/*
    We can use #define HOT_SWAP
    to choose whether to use logs function with 
    SD hot swap feature or not
*/
//#define HOT_SWAP

void logs();

#endif