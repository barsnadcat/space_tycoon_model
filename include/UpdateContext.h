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
		mRandomEngine.seed(seed);
	}
	uint32_t mCurrentTime { 0 };
	std::mt19937 mRandomEngine;
	std::map<ProductId, ObjectiveUtility> mObjectiveUtilities;
	std::map<ProductionId, std::vector<ProductionConfig>> mProductions;
};
