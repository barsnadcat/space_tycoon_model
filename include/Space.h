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
	void Add(ProductId productId, ObjectSP object);
	ObjectSPs& Get(ProductId productId) { return mContent[productId]; }
private:
	Object& mThisObject;
	std::map<ProductId, ObjectSPs> mContent;
};
