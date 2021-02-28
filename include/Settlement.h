#pragma once

#include <Object.h>
#include <cassert>

class Settlement
{
public:
	Settlement(Object& thisObject): mThisObject(thisObject)
	{
	}
	void Update(UpdateContext& uc);
private:
	Object& mThisObject;
};

ObjectSP ConstructSettlement();
