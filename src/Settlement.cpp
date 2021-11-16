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
