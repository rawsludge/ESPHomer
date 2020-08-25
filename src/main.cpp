#include <Arduino.h>
#include "ESPHomer.hpp"

void setup() 
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    Homer.setup();
}

void loop()
{
    Homer.loop();
}

