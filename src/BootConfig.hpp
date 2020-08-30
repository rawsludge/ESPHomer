#include "IBoot.hpp"
#include <ESP8266WiFi.h>
#include <ArduinoLog.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>
//#include <WiFiManager.h>
#include <Ticker.h>

class BootConfig : public IBoot
{
private:
    //WiFiManager     _wifiManager;
    ESP8266WebServer    _http;
    Ticker              _ticker;
private:    
    static const int MAX_POST_SIZE = 1500;
public:
    BootConfig(/* args */);
    ~BootConfig();
    void loop();
    void setup();
};
