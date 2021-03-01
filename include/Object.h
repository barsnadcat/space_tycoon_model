#pragma once

#include <memory>
#include <vector>
#include <EntitiesDeclarations.h>

class Entity;
class Space;
class Property;
class Owner;
class Food;
class Settlement;
class Person;
struct UpdateContext;

class Object: public std::enable_shared_from_this<Object>
{
public:
	Object(ObjectId objectId);
	~Object();
	void Update(UpdateContext& uc);
	const ObjectId id;
	std::unique_ptr<Entity> entity;
	std::unique_ptr<Space> space;
	std::unique_ptr<Property> property;
	std::unique_ptr<Owner> owner;
	std::unique_ptr<Food> food;
	std::unique_ptr<Settlement> settlement;
	std::unique_ptr<Person> person;
};

using ObjectSP = std::shared_ptr<Object>;
using ObjectWP = std::weak_ptr<Object>;
using ObjectSPs = std::vector<ObjectSP>;
using ObjectWPs = std::vector<ObjectWP>;
