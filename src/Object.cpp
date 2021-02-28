#include <Object.h>

#include <Entity.h>
#include <Space.h>
#include <Settlement.h>
#include <Property.h>
#include <Owner.h>
#include <Food.h>
#include <UpdateContext.h>

Object::Object() {}
Object::~Object() {}

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
