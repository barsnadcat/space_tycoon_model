#pragma once

#include "ISpace.h"

void Update(IEntityIterator::Shared it)
{
	while (it->HasNext())
	{
		IEntity::Shared pEntity = it->Get();
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
