#include <Arduino.h>
#include "Definitions.h"

namespace Internals
{
    class HelperClass
    {
    private:
        char _deviceID[MAX_WIFI_SSID_LENGTH];

    public:
        HelperClass(/* args */);
        ~HelperClass();

        char *getID();
        void setID(const char *id);
    };
    
    extern HelperClass Helpers;     
}