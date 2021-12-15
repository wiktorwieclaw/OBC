#include <Arduino.h>
#include "bmp_280.h"

BMP280 bmp;
double T,P,A;

void bmp_setup()
{
    Serial.println("Initializing bmp module...");
    if(!bmp.begin()){
        Serial.println("BMP init failed!");
        while(1);
    }
    else 
        Serial.println("BMP init success!\n\n");
    bmp.setOversampling(4);
}

void bmp_measure(double &T, double &P, double &A)
{
    char result = bmp.startMeasurment();
    
    if(result!=0){
        delay(result);
        result = bmp.getTemperatureAndPressure(T,P);
        if(result!=0)
        {
            A = bmp.altitude(P,P0);
            P+=26.50;   //roznica pomiarow
            #ifdef POMIARY_NA_SERIALU
            Serial.print("T = ");Serial.print(T,2); Serial.print("degC\t");
            Serial.print("P = ");Serial.print(P,2); Serial.print("mBar\t");
            Serial.print("A = ");Serial.print(A,2); Serial.println("m");
            #endif
            
        }
        else {
            Serial.println("Blad pomiaru.");
        }
    }
    else {
        Serial.println("Blad pomiaru.");
    }
}