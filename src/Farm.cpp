#include <Farm.h>

#include <Entity.h>
#include <Property.h>

ObjectSP ConstructFarm(uint32_t health)
{
    auto object = std::make_shared<Object>(kFarmId);
    object->entity = std::make_unique<Entity>(health);
	object->property = std::make_unique<Property>();
    return object;
}