#pragma once

#include "Space.h"

void UpdateSpace(Space& space)
{
	SpaceIterator it = space.GetSpaceIterator();
	while (it.HasNext())
	{
		Entity& entity = it.Get();
		UpdateSpace(entity);
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
