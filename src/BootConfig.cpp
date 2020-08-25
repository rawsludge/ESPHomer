#include "BootConfig.hpp"

BootConfig::BootConfig():
    _portal(_server)
{

}

void BootConfig::setup()
{
    _config.autoReconnect = true;
    _portal.config(_config);
    if( _portal.begin() ) {
        Log.notice("WiFi connected: %s" CR, WiFi.localIP().toString().c_str());        
    }
}

void BootConfig::loop()
{
    _portal.handleClient();
}