#pragma once

#include <memory>
#include <vector>

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
	Object();
	~Object();
	void Update(UpdateContext& uc);

	std::unique_ptr<Entity> mEntity;
	std::unique_ptr<Space> mSpace;
	std::unique_ptr<Property> mProperty;
	std::unique_ptr<Owner> mOwner;
	std::unique_ptr<Food> mFood;
	std::unique_ptr<Settlement> mSettlement;
	std::unique_ptr<Person> mPerson;
};

using ObjectSP = std::shared_ptr<Object>;
using ObjectWP = std::weak_ptr<Object>;
using ObjectSPs = std::vector<ObjectSP>;
using ObjectWPs = std::vector<ObjectWP>;
