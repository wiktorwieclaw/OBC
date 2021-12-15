#include <Arduino.h>
#include "sd_card.h"


void sd_setup()
{
    Serial.println("Initializing sd card...");
    if(!SD.begin(CHIP_SELECT)) {
        Serial.println("Error of initializing sd card");
        return;
    }
    Serial.println("Initializing compelete\n\n");
}

void sd_log(double T, double P, double A)
{
    File file = SD.open(FILENAME, FILE_WRITE);

    if(file){
        file.print("T = ");file.print(T,2); file.print("degC\t");
        file.print("P = ");file.print(P,2); file.print("mBar\t");
        file.print("A = ");file.print(A,2); file.println("m");
    }

    file.close();
}