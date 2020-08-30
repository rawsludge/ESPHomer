#include "BootConfig.hpp"
#include "Helpers.hpp"
#include "UtilsClass.hpp"

using namespace Internals;

BootConfig::BootConfig() : 
    _http(80)
{
    Log.notice("Starting config mode" CR);             
    WiFi.disconnect(true);
}

void BootConfig::setup()
{
    char hostname[MAX_WIFI_SSID_LENGTH]={0};
    sprintf(hostname, "%s_%s", "ESPHomer", Helpers::getID());
    Log.notice("SSID:%s" CR, hostname);
    wifi_station_set_hostname(hostname);
    WiFi.hostname(hostname);    
    
    _ticker.attach_ms(CONFIG_LED_TIME, []() {
        int status = digitalRead(LED_BUILTIN);
        digitalWrite(LED_BUILTIN, !status);
    });

    WiFi.mode(WIFI_AP);
    WiFi.softAP(hostname);
    Log.notice("AP IP Address: %s" CR, WiFi.softAPIP().toString().c_str());

    ESP8266WebServer *server = &_http;
    _http.on("/config", HTTP_PUT, [server, ticker=&_ticker](){
        Log.notice("Configuration begin" CR);
        if( server->hasArg("plain") )
        {
            const char *data = server->arg("plain").c_str();
            bool result = Utils.Config()->save(data);
            if( !result ) 
            {
                String message = String("{\"success\":false") + String("\"error\":\"") + String(Helpers::getLastError()) + String("\"}");
                server->send(400, "application/json", message.c_str());
                return;
            }
            server->send(200, "application/json", "{\"success\":true}");
            Log.notice("Device configured" CR);
            ticker->detach();
            ticker->attach_ms(2000, []() { 
                digitalWrite(LED_BUILTIN, 0);
                ESP.reset();
            });
        }
    });
    _http.begin();
}

void BootConfig::loop()
{
    _http.handleClient();
}