#include "ESPHomer.hpp"

ESPHomer::ESPHomer()
{

}

void ESPHomer::setup()
{
    Log.begin( LOG_LEVEL_VERBOSE, &Serial );
    pinMode(LED_BUILTIN, OUTPUT);

    Log.trace("Config loading" CR);
    bool mode = Utils.Config()->load();
    Log.trace("Config loaded. Result: %t" CR, mode);
    if( !mode ) 
    {   
        _boot = new BootConfig();
    }
    else
    {
        _boot = new BootNormal();
    }
    
    Log.notice("OK" CR);

    _boot->setup();
}

void ESPHomer::loop()
{
    _boot->loop();
}

ESPHomer::~ESPHomer()
{

}

ESPHomer Homer = ESPHomer();