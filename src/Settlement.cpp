#include <Settlement.h>

#include <Space.h>
#include <Food.h>

ObjectSP ConstructSettlement()
{
	auto settlement = std::make_shared<Object>();
	settlement->mSpace = std::make_unique<Space>(settlement);
	settlement->mSettlement = std::make_unique<Settlement>(settlement);
	return settlement;
}

void Settlement::Update(UpdateContext& uc)
{
	mThisObject.lock()->mSpace->AddFood(ConstructFood(100));
}
