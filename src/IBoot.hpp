
#pragma once

class IBoot
{
private:
    /* data */
public:
    virtual void setup() = 0;
    virtual void loop() = 0;    

};