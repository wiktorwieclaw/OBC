#include <Arduino.h>
//#include <math.h>
#include <SPI.h>
#include <SD.h>
#include "BMP280.h"
#include "Wire.h"
#include "SparkFun_MMA8452Q.h"
#include "logs.h"
#include "bmp.h"

File myFile;
int state = 0;
BMP280 bmp;
int cardIn,cardButton;
double T,P,A;
char result; 


void debug();

void setup()
{
  _init();
}

void loop()
{
  measurments();
  logs();
  debug();
}


void debug(){
  Serial.print("T = \t");Serial.print(T,2); Serial.print(" degC\t");
  Serial.print("P = \t");Serial.print(P,2); Serial.print(" mBar\t");
  Serial.print("A = \t");Serial.print(A,2); Serial.println(" m");
}


