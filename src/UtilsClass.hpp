#pragma once
#include "DeviceConfig.hpp"

namespace Internals
{
    class UtilsClass
    {
    private:
        DeviceConfig *_deviceConfig;
    public:
        UtilsClass(/* args */);
        DeviceConfig *Config();
        ~UtilsClass();
    };

    extern UtilsClass Utils;
}