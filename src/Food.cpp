#include <Food.h>

#include <Property.h>
#include <Entity.h>

ObjectSP ConstructFood(uint32_t health)
{
    auto object = std::make_shared<Object>(kFoodId);
    object->entity = std::make_unique<Entity>(health);
	object->property = std::make_unique<Property>();
    object->food = std::make_unique<Food>();
    return object;    
}