#include "Settlement.h"

void Settlement::OnSpaceUpdated(UpdateContext& uc)
{
	AddFood(std::make_unique<Food>(100));
}
