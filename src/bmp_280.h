#include <Arduino.h>
#include "BMP280.h" 
#include "Wire.h"

extern double T,P,A;    //temperatura cisnienie wysokosc
void bmp_setup();
void bmp_measure(double &T, double &P, double &A);

#define P0 1012.5
#define POMIARY_NA_SERIALU