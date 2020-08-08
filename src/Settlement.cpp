#include "Settlement.h"

void Settlement::OnSpaceUpdated()
{
	AddFood(std::make_unique<Food>(100));
}
