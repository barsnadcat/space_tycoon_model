#include <Property.h>
#include <Owner.h>

Object* Property::GetOwner() const
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

void Property::SetOwner(ObjectSP owner)
{
	mOwner = owner;
}
