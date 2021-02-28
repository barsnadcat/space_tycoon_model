#include <Object.h>

#include <Entity.h>
#include <Space.h>
#include <Settlement.h>
#include <Property.h>
#include <Owner.h>
#include <Food.h>
#include <Person.h>
#include <UpdateContext.h>

Object::Object() {}
Object::~Object() {}

void Object::Update(UpdateContext& uc)
{
	if (entity)
	{
		entity->Update(uc);
	}
	if (space)
	{
		space->Update(uc);
	}
	if (settlement)
	{
		settlement->Update(uc);
	}
	if (person)
	{
		person->Update(uc);
	}
}
