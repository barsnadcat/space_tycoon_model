#pragma once

#include "Space.h"

void Update(SpaceIterator&& it)
{
	while (it.HasNext())
	{
		Entity::Shared pEntity = it.Get();
		Update(pEntity->GetSpaceIterator());
		pEntity->Update();
		if (pEntity->GetHealth() == 0)
		{
			it.Remove();
		}
		else
		{
			it.Next();
		}
	}
}
