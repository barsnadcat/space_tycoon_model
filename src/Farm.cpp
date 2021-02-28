#include <Farm.h>

#include <Entity.h>
#include <Property.h>

ObjectSP ConstructFarm(uint32_t health)
{
    auto object = std::make_shared<Object>();
    object->mEntity = std::make_unique<Entity>(health);
	object->mProperty = std::make_unique<Property>();
    return object;
}