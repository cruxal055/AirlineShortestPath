#include "airport.h"

airport::airport()
{
    name = "";
    code = 0;
}

airport::airport(const string &name, int code)
{
    this->name = name;
    this->code = code;
}


airport::airport(const airport &other)
{
    copyOther(other);

}

airport& airport::operator=(const airport &other)
{
    if(this != &other)
    {
        copyOther(other);
    }
    return *this;
}

bool airport::operator<(const airport& other) const
{
   return code < other.code ;  //assume that you compare the record based on a
}

void airport::copyOther(const airport &other)
{
    name = other.name;
    code = other.code;
}
