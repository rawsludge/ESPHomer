#pragma once
#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoLog.h>
#include "IBoot.hpp"
#include "BootConfig.hpp"
#include "BootNormal.hpp"
#include "DeviceConfig.hpp"
#include "UtilsClass.hpp"


using namespace Internals;

class ESPHomer
{
private:
    IBoot *_boot;
public:
    ESPHomer(/* args */);
    ~ESPHomer();
    void setup();
    void loop();
};
extern ESPHomer Homer;

