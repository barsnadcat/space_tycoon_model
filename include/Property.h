#pragma once

#include <memory>
#include <EntitiesDeclarations.h>

class Property
{
public:
	Object* GetOwner() const;
	void SetOwner(ObjectSP owner);
private:
	ObjectWP mOwner;
};
