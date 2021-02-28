#include <Settlement.h>
#include <Entity.h>
#include <Food.h>
#include <Space.h>
#include <Owner.h>

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
