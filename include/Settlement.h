#pragma once

#include <Object.h>
#include <cassert>

class Settlement
{
public:
	Settlement(ObjectSP thisObject): mThisObject(thisObject)
	{
		assert(thisObject);
	}
	void Update(UpdateContext& uc);
private:
	ObjectWP mThisObject;
};

ObjectSP ConstructSettlement();
