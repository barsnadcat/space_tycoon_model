#include <Property.h>

Person* Property::GetOwner() 
{
    if (auto p = mOwner.lock())
    {
        return p.get();
    }
    else
    {
        return nullptr;        
    }
}