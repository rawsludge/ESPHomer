#pragma once
#include <Arduino.h>
#include <ArduinoLog.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include "IBoot.hpp"
#include "UtilsClass.hpp"

class BootNormal : public IBoot
{
private:
    Ticker      _ticker;
public:
    BootNormal(/* args */);
    void loop();
    void setup();    
    ~BootNormal();
};
