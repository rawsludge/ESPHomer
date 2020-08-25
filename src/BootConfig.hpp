#include "IBoot.hpp"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AutoConnect.h>
#include <ArduinoLog.h>

class BootConfig : public IBoot
{
private:
    ESP8266WebServer    _server;
    AutoConnect         _portal;
    AutoConnectConfig   _config;

public:
    BootConfig(/* args */);
    ~BootConfig();
    void loop();
    void setup();
};
