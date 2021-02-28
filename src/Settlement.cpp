#include <Settlement.h>
#include <Food.h>
#include <Space.h>
#include <Owner.h>

std::shared_ptr<Settlement> ConstructSettelment()
{
	auto settelment = std::make_shared<Settlement>();
	settelment->mSpace = std::make_unique<Space>(settelment);
	return settelment;
}

void Settlement::OnObjectUpdated(UpdateContext& uc)
{
	mSpace->AddFood(std::make_shared<Food>(100));
}
