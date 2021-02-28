#pragma once

#include <Object.h>
#include <Space.h>

class Settlement: public Object
{
public:
	virtual void OnObjectUpdated(UpdateContext& uc) override;
};

std::shared_ptr<Settlement> ConstructSettelment();
