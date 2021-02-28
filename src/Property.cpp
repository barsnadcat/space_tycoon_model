#include <Owner.h>
#include <Property.h>

ObjectSP Property::GetOwner() const
{
	return mOwner.lock();
}

void Property::SetOwner(ObjectSP owner)
{
	mOwner = owner;
}
