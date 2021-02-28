#pragma once

#include <memory>

class Entity;
class Space;
class Property;
class Owner;
struct UpdateContext;

class Object: public std::enable_shared_from_this<Object>
{
public:
	void Update(UpdateContext& uc);
	virtual void OnObjectUpdated(UpdateContext& uc) {}

	std::unique_ptr<Entity> mEntity;
	std::unique_ptr<Space> mSpace;
	std::unique_ptr<Property> mProperty;
	std::unique_ptr<Owner> mOwner;
};
