#pragma once

#include "Space.h"

void Update(IEntityIterator::Shared it)
{
	while (it->HasNext())
	{
		Entity::Shared pEntity = it->Get();
		Update(pEntity->GetEntityIterator());
		pEntity->Update();
		if (pEntity->GetHealth() == 0)
		{
			it->Remove();
		}
		else
		{
			it->Next();
		}
	}
}
