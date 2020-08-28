#include "IBoot.hpp"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoLog.h>
#include <WiFiManager.h>
#include <Ticker.h>

class BootConfig : public IBoot
{
private:
    WiFiManager     _wifiManager;
    Ticker          _ticker;
public:
    BootConfig(/* args */);
    ~BootConfig();
    void loop();
    void setup();
};
