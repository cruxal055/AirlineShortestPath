#include "airline.h"

airline::airline()
{
    airName = "";
    airlineID = 0;
}

airline::airline(string airName, int id)
{
    this->airName = airName;
    this->airlineID = id;
}

airline::airline(const airline &other)
{
    copy(other);
}

airline& airline::operator=(const airline &other)
{
    if(this != &other)
    {
        copy(other);
    }
    return *this;
}

airline::~airline()
{

}

void airline::copy(const airline &other)
{
    this->airName = other.airName;
    this->airlineID = other.airlineID;
}
