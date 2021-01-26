#pragma once

#include "Person.h"
#include "Space.h"

#include <memory>
#include <vector>

class Settlement: public Space
{
public:
	virtual void OnSpaceUpdated(UpdateContext& uc) override;
};
