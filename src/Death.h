#pragma once

#include "ISpace.h"

void Death(IEntityIterator::Shared it)
{
	while (it->HasNext())
	{
		IEntity::Shared pEntity = it->Get();
		Death(pEntity->GetEntityIterator());
		pEntity->DecayMaxHealth(1);
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
