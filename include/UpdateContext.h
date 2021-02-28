#pragma once
#include <random>
#include <cstdint>
#include <vector>
#include <ObjectiveUtility.h>
#include <EntitiesDeclarations.h>
#include <ProductionsConfig.h>

struct UpdateContext
{
	UpdateContext(int32_t seed = 1)
	{
		randomEngine.seed(seed);
	}
	uint32_t currentTime { 0 };
	std::mt19937 randomEngine;
	std::map<ProductId, ObjectiveUtility> objectiveUtilities;
	std::map<ProductionId, std::vector<ProductionConfig>> productions;
};
