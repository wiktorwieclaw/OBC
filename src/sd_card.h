#include <SPI.h>  
#include <SD.h>   


void sd_setup();
void sd_log(double T, double P, double A);

#define CHIP_SELECT D9
#define FILENAME "FINAL.txt"