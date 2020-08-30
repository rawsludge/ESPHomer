#include "UtilsClass.hpp"


using namespace Internals;

Internals::UtilsClass Internals::Utils = Internals::UtilsClass();

UtilsClass::UtilsClass(/* args */)
{
    _deviceConfig = NULL;
}

DeviceConfig *UtilsClass::Config()
 {
    if(_deviceConfig == NULL )
        _deviceConfig = new DeviceConfig();
    return _deviceConfig;
}

UtilsClass::~UtilsClass()
{
}