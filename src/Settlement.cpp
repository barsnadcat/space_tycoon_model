#include <Settlement.h>

#include <Land.h>

Settlement::Settlement(size_t landSize): Entity(nullptr, 1, 0)
{
	mLands.resize(landSize);
	for (size_t i = 0; i < landSize; i++)
	{
		mLands[i].reset(new Land(this, i));
	}
}

Settlement::~Settlement()
{
}

Land* Settlement::GetNeighbour(Land* pLand) const
{
	assert(pLand);
	size_t nieghbour = pLand->GetIndex() + 1;
	if (nieghbour >= mLands.size())
	{
		nieghbour = 0;
	}
	return mLands[nieghbour].get();
}
