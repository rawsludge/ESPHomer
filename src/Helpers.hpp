#pragma once

#include <Arduino.h>
#include "Definitions.h"

namespace Internals
{
    class DeviceConfig;

    class Helpers
    {
    private:
        static char _deviceID[MAX_MAC_LENGTH];
        static char _lastError[81];
        friend class DeviceConfig;
    public:
        static const char *getID();
        static const char *getLastError();
    };
}