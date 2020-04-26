#pragma once

#include "Space.h"

void Update(Space& space)
{
	SpaceIterator it = space.GetSpaceIterator();
	while (it.HasNext())
	{
		Entity& entity = it.Get();
		Update(entity);
		entity.Update();
		if (entity.GetHealth() == 0)
		{
			it.Remove();
		}
		else
		{
			it.Next();
		}
	}
}
