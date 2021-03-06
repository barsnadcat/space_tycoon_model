#pragma once
#include <map>
#include <vector>
#include <EntitiesDeclarations.h>

struct ProductionConfig
{
	ObjectId productId = kInvalidId;
	int32_t number = 0;
	bool tool = false;
};

std::map<ProductionId, std::vector<ProductionConfig>> GetProductions();
