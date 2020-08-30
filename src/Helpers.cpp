#include "Helpers.hpp"

using namespace Internals;

char Helpers::_deviceID[] = {0};
char Helpers::_lastError[] = {0};

const char *Helpers::getID()
{
    if(strncmp(_deviceID, "", MAX_MAC_LENGTH) == 0)
        sprintf(_deviceID, "%06X", ESP.getChipId());
    return Helpers::_deviceID;;
}

const char *Helpers::getLastError()
{
    return Helpers::_lastError;
}
