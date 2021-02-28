#include <Object.h>

#include <Entity.h>
#include <Space.h>
#include <Settlement.h>

void Object::Update(UpdateContext& uc)
{
	if (mEntity)
	{
		mEntity->Update(uc);
	}
	if (mSpace)
	{
		mSpace->Update(uc);
	}
	if (mSettlement)
	{
		mSettlement->Update(uc);
	}
	OnObjectUpdated(uc);
}
