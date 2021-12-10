#include <Arduino.h>
//#include <math.h>
#include <SPI.h>
#include <SD.h>
#include "BMP280.h"
#include "Wire.h"
#include "bmp.h"

extern BMP280 bmp;
extern int cardIn,cardButton;
extern double T,P,A;
extern char result; 

void _init()
{
  Serial.begin(9600);
  while (!Serial) {}
  pinMode(D9,INPUT_PULLUP);
  pinMode(STATUS_GREEN_PIN,OUTPUT);
  pinMode(STATUS_RED_PIN,OUTPUT);
  pinMode(HOT_SWAP_BUTTON,INPUT_PULLUP);
  if(!bmp.begin()){
    Serial.println("BMP init failed!");
    //while(1);
  }
  else Serial.println("BMP init success!");
  bmp.setOversampling(4);

  #ifdef HOT_SWAP
  if (!SD.begin(D10)) {
       Serial.println("initialization failed!");
       while(1){};
  }
  #endif
}

void measurments()
{
  cardIn = digitalRead(D9);
  cardButton = pulseIn(HOT_SWAP_BUTTON, HIGH, 100000);
  result = bmp.startMeasurment();
  if(result!=0){
    delay(result);
    result = bmp.getTemperatureAndPressure(T,P);
    if(result!=0){
      A = bmp.altitude(P,P0);
    }
    else {
        Serial.println("Error.");
    }
  }
  else {
    Serial.println("Error.");
  }
}