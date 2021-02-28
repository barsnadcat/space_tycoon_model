#include <Object.h>

#include <Entity.h>
#include <Space.h>

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
	OnObjectUpdated(uc);
}
