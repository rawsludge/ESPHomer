#include "BootNormal.hpp"

using namespace Internals;

BootNormal::BootNormal(/* args */)
{
    Log.notice("Starting normal mode" CR);             
}

void BootNormal::setup() 
{
    WiFi.mode(WIFI_STA);    
    WiFi.setAutoReconnect(true);
    char *ssid = Utils.Config()->Details().wifi.ssid;
    char *passd = Utils.Config()->Details().wifi.password;
    wl_status_t status = WiFi.begin(ssid, passd);
    Log.notice("Connecting wifi. SSID:%s, Pass: '****'" CR, ssid);

    _ticker.attach_ms(WIFI_LED_TIME, []() {
        int status = digitalRead(LED_BUILTIN);
        digitalWrite(LED_BUILTIN, !status);
    });
    
    Log.trace("Connecting WiFi...");
    while (status != WL_CONNECTED)
    {
        status = WiFi.status();
        delay(500);
    }
    Log.notice( CR "Connected WiFi. IP: %s" CR, WiFi.localIP().toString().c_str());
    _ticker.detach();

    _ticker.attach_ms(MQTT_LED_TIME, []() {
        int status = digitalRead(LED_BUILTIN);
        digitalWrite(LED_BUILTIN, !status);
    });
}

void BootNormal::loop()
{

}

BootNormal::~BootNormal()
{
}
