#include "HelperClass.hpp"

using namespace Internals;

HelperClass::HelperClass(/* args */)
{
    setID("ESPHomer");
}

char *HelperClass::getID() 
{
    return _deviceID;
}
void HelperClass::setID(const char *id) {
    sprintf(_deviceID, "%s_%06X", id, ESP.getChipId());
}        

HelperClass::~HelperClass()
{
}

HelperClass Internals::Helpers = HelperClass();    
