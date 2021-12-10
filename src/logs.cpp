#include <Arduino.h>
//#include <math.h>
#include <SPI.h>
#include <SD.h>
#include "BMP280.h"
#include "Wire.h"
#include "logs.h"


extern File myFile;
extern int state;
extern BMP280 bmp;
extern int cardIn,cardButton;
extern double T,P,A;
extern char result; 


#ifdef HOT_SWAP
void logs()
{
  myFile = SD.open("test.txt", FILE_WRITE);
  Serial.println("Disk is ready!");   
  if (myFile) {
    myFile.print("Temperatura: ");  myFile.print(T,2); myFile.print(" degC\t");
    myFile.print("Ciśnienie: ");    myFile.print(P,2); myFile.print(" mBar\t");
    myFile.print("Wysokość npm: "); myFile.print(A,2); myFile.println(" m");   
   }
  myFile.close();
}
#endif

#ifndef HOT_SWAP
void logs()
{
  //int state:
  //  0 - there is no disk to save data
  //  1 - disk is ready to be removed
  //  2 - disk is ready and data can be saved
  //
  //button is used to switch disk state. When disk normaly works,
  //it could be risky to remove drive. 


  if(cardButton != 0)
  {
     state = 1;
  }
  if(cardIn == HIGH)
  {
    bool diskReady = true;
    if (!SD.begin(D10)) {
       Serial.println("initialization failed!");
       diskReady = false;
    }
    if(diskReady)
    {
      myFile = SD.open("test.txt", FILE_WRITE);
      digitalWrite(STATUS_RED_PIN,LOW);
      digitalWrite(STATUS_GREEN_PIN,HIGH);

      if(state == 0) state = 2;
      if(state == 2) {
        Serial.println("Disk is ready!");   
        if (myFile) {
            myFile.print("Temperatura: ");  myFile.print(T,2); myFile.print(" degC\t");
            myFile.print("Ciśnienie: ");    myFile.print(P,2); myFile.print(" mBar\t");
            myFile.print("Wysokość npm: "); myFile.print(A,2); myFile.println(" m");   
         }
       }
      else if (state == 1)
      {
        Serial.println("You cane remove device!");
        int switchmilis = (millis()/500)%2;
        if(switchmilis == 0)digitalWrite(STATUS_GREEN_PIN,HIGH);
        else digitalWrite(STATUS_GREEN_PIN,LOW);
      }
       myFile.close();
    }
  }
  else
  {
    digitalWrite(STATUS_GREEN_PIN,LOW);
    digitalWrite(STATUS_RED_PIN,HIGH);
    Serial.println("There is no disk!");
    state = 0;
  }
}

#endif