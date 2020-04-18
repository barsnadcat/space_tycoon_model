#pragma once

#include "IEntityContainer.h"

void Death(IEntityIterator::Shared it)
{
	while (it->HasNext())
	{
		IEntity::Shared pEntity = it->Next();
		Death(pEntity->GetEntityIterator());
		pEntity->DecayMaxHealth(1);
		if (pEntity->GetHealth() == 0)
		{
			it->Remove();
		}

	}
}
