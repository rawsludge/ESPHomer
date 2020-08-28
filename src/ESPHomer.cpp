#include "ESPHomer.hpp"


ESPHomer::ESPHomer()
{

}

void ESPHomer::setup()
{
    Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);

    if(!LittleFS.begin()) {
        Log.fatal("FS can't start." CR);
        abort();
    }
    bool mode = LittleFS.exists("config.json");

    if( !mode ) 
    {   
        Log.notice("Starting config mode" CR);             
        _boot = new BootConfig();
    }

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