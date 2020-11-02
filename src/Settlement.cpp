#include "Settlement.h"


void Settlement::OnSpaceUpdated(UpdateContext& uc)
{
	AddFood(std::make_shared<Food>(100));
}
