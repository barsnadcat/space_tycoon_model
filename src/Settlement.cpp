#include <Settlement.h>

#include <Space.h>
#include <Food.h>

ObjectSP ConstructSettlement()
{
	auto settlement = std::make_shared<Object>(kSettlementId);
	settlement->space = std::make_unique<Space>(*settlement);
	settlement->settlement = std::make_unique<Settlement>(*settlement);
	return settlement;
}

void Settlement::Update(UpdateContext& uc)
{
	mThisObject.space->Add(ConstructFood(100));
}
