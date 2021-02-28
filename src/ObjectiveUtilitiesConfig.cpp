#include <ObjectiveUtilitiesConfig.h>

std::map<ProductId, ObjectiveUtility> GetObjectiveUtilities()
{
    // It is possible to setup such a high cost for productions, that it will never be selected with average preferences levels...
    // Can we have more transparent production value setup?
    // May be we should place values instead of quantities in production configs?
	std::map<ProductId, ObjectiveUtility> res;
	res.emplace(std::make_pair(kFoodId, ObjectiveUtility(75.0f, 20, 30, 100)));
	res.emplace(std::make_pair(kFarmId, ObjectiveUtility(100.0f, 1, 2, 3)));
	res.emplace(std::make_pair(kEffortId, ObjectiveUtility(10.0f, 100, 1000, 2000)));
	res.emplace(std::make_pair(kFamilyMemberId, ObjectiveUtility(200.0f, 2, 5, 20)));
	res.emplace(std::make_pair(kRandomProductId, ObjectiveUtility(50.0f, 20, 30, 100)));
	return res;
}
