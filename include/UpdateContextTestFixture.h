#pragma once

#include <gtest/gtest.h>
#include <UpdateContext.h>
#include <ObjectiveUtilitiesConfig.h>
#include <ProductionsConfig.h>

class UpdateContextTestFixture: public ::testing::Test
{
protected:
	void SetUp() override
	{
		uc = UpdateContext();
		uc.mObjectiveUtilities = GetObjectiveUtilities();
		uc.mProductions = GetProductions();
	}

	UpdateContext uc;
};
