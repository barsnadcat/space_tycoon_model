#pragma once

#include <EntitiesDeclarations.h>
#include <Object.h>

#include <memory>
#include <map>

class Owner
{
public:
	Owner(Object& thisObject): mThisObject(thisObject) {}
	void Claim(ProductId productId, ObjectSP object);
	ObjectWPs& GetOwned(ProductId productId) { return mProperty[productId]; }
	int32_t GetOwnedCount(ProductId productId) const;
	ObjectSP GetMyNearFood();
private:
	Object& mThisObject;
	std::map<ProductId, ObjectWPs> mProperty;
};
