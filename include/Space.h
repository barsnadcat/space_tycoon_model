#pragma once

#include <EntitiesDeclarations.h>
#include <Object.h>

#include <memory>
#include <vector>
#include <map>

struct UpdateContext;

class Space
{
public:
	Space(Object& thisObject): mThisObject(thisObject) {}
	void Update(UpdateContext& uc);
	void Add(ObjectSP object);
	ObjectSPs& Get(ObjectId objectId) { return mContent[objectId]; }
private:
	Object& mThisObject;
	std::map<ObjectId, ObjectSPs> mContent;
};
