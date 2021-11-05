#include <Space.h>

#include <Land.h>
#include <cassert>

Space::Space(size_t landSize): Entity(nullptr, 1, 0)
{
	mLands.resize(landSize);
	for (size_t i = 0; i < landSize; i++)
	{
		mLands[i].reset(new Land(this, i));
	}
}
