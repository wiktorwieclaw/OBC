#include <Arduino.h>
#include <math.h>
#include <SPI.h>
#include <SD.h>
#include "BMP280.h"
#include "Wire.h"
#include "SparkFun_MMA8452Q.h"

#define P0 1013.25
#define STATUS_GREEN_PIN A2
#define STATUS_RED_PIN A1
#define HOT_SWAP_BUTTON A3
BMP280 bmp;
File myFile;
int cardIn,cardButton;
double T,P,A;
char result;
MMA8452Q accel;    
int state = 0;

void _init();
void measurments();
void logs();
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

void logs(){
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
               if(state == 0) state = 2;
               if(state == 2) {
                 Serial.println("Disk is ready!");   
                 if (myFile) {
                     myFile.print("Temperatura: ");  myFile.print(T,2); myFile.print(" degC\t");
                     myFile.print("Ciśnienie: ");    myFile.print(P,2); myFile.print(" mBar\t");
                     myFile.print("Wysokość npm: "); myFile.print(A,2); myFile.println(" m");   
                 }
                 digitalWrite(STATUS_GREEN_PIN,HIGH);
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
void debug(){
  Serial.print("T = \t");Serial.print(T,2); Serial.print(" degC\t");
  Serial.print("P = \t");Serial.print(P,2); Serial.print(" mBar\t");
  Serial.print("A = \t");Serial.print(A,2); Serial.println(" m");
}


/*void setiup(){

 // initialize LED digital pin as an output.
  //pinMode(A0,INPUT_PULLUP);
  //pinMode(A1,INPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  


/*void loop()
{
  int duration = pulseIn(A0, HIGH);
  //if(duration != 0) Serial.println(duration);
 
  if(duration != 0)
  {
    state = state == 3 ? 0 : state+1;
  }
    //while(digitalRead(A0) == LOW){}
    switch(state)
    {
        case 0:{
          digitalWrite(A2,HIGH);
          digitalWrite(A3,LOW);
          digitalWrite(A4,LOW);
        }break;
        case 1:{
          digitalWrite(A2,LOW);
          digitalWrite(A3,HIGH);
          digitalWrite(A4,LOW);
        }break;
        case 2:{
          digitalWrite(A2,LOW);
          digitalWrite(A3,LOW);
          digitalWrite(A4,HIGH);
        }break;

    }
    //if(digitalRead(A1) == HIGH) 
    //else digitalWrite(A2,HIGH);
    //digitalWrite(A2,LOW);


  //Serial.printf("Hello world!\r\n");
  //digitalWrite(A2,HIGH);
  /*analogWrite(A2,50 + 100*sin(((120*PI/360) + t*PI/360)));
  delay(20);
  ++t;
  if(t>=120) t = 0;
}*/
