#include <Arduino.h>
#include "bmp_280.h"
#include "sd_card.h"

void setup() {

  Serial.begin(9600);
  while(!Serial) {}

  sd_setup();
  bmp_setup();
}

void loop() {
  bmp_measure(T, P, A);
  sd_log(T,P,A);
  delay(1000);
}