#include <Property.h>
#include <Owner.h>

Owner* Property::GetOwner() const
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

void Property::SetOwner(std::shared_ptr<Owner> owner)
{
    mOwner = owner;
}