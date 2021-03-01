#pragma once

#include <EntitiesDeclarations.h>
#include <Object.h>

#include <memory>
#include <map>

class Owner
{
public:
	Owner(Object& thisObject): mThisObject(thisObject) {}
	void Claim(ObjectSP object);
	ObjectWPs& GetOwned(ObjectId objectId) { return mProperty[objectId]; }
	int32_t GetOwnedCount(ObjectId objectId) const;
	ObjectSP GetMyNearFood();
private:
	Object& mThisObject;
	std::map<ObjectId, ObjectWPs> mProperty;
};
