#include "BootConfig.hpp"
#include "HelperClass.hpp"

using namespace Internals;

BootConfig::BootConfig()
{
    WiFi.disconnect(true);
}

void BootConfig::setup()
{
    char *hostname = Helpers.getID();
    Log.notice("SSID:%s" CR, hostname);
    wifi_station_set_hostname(hostname);
    WiFi.hostname(hostname);    

    pinMode(LED_BUILTIN, OUTPUT);

    _ticker.attach_ms(800, []() {
        int status = digitalRead(LED_BUILTIN);
        digitalWrite(LED_BUILTIN, !status);
    });

    _wifiManager.setAPCallback( [&](WiFiManager *wifiM) {
        Log.notice("Config mode ip: %s, SSID: %s" CR, WiFi.softAPIP().toString().c_str(), wifiM->getConfigPortalSSID().c_str() );        
    });    
    _wifiManager.setSaveConfigCallback( [=]() {
        Log.notice("Config callback called" CR);

    } );

    _wifiManager.setBreakAfterConfig(true);
    _wifiManager.setConfigPortalTimeout(120);
    if( !_wifiManager.startConfigPortal( hostname ))
    {
        Log.error("Failed to connect and hit timeout" CR);  
        ESP.reset();
        delay(1000);
    }
    _ticker.detach();
}

void BootConfig::loop()
{

}