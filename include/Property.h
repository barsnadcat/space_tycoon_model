#pragma once

#include <memory>
#include <Object.h>

class Property
{
public:
	ObjectSP GetOwner() const;
	void SetOwner(ObjectSP owner);
private:
	ObjectWP mOwner;
};
