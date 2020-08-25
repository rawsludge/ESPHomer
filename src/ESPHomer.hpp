#pragma once
#include <LittleFS.h>
#include <ArduinoLog.h>
#include "IBoot.hpp"
#include "BootConfig.hpp"


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

