#pragma once

#include <LittleFS.h>
#include <ArduinoLog.h>
#include "ConfigStruct.hpp"
#include "Helpers.hpp"

namespace Internals
{    
    class DeviceConfig
    {
    private:
        struct ConfigStruct _configStruct;
        bool _fileSystem;
        bool _configValid;
    private:
        bool initFileSystem();
        bool load(const char* config);
    public:
        DeviceConfig(/* args */);
        ~DeviceConfig();

        bool load();
        bool save();
        bool save(const char*buffer);
        struct ConfigStruct Details();
    };
}