#include <ProductionsConfig.h>

std::map<ProductionId, std::vector<std::pair<ProductId, int32_t>>> GetProductions()
{
    auto res = std::map<ProductionId, std::vector<std::pair<ProductId, int32_t>>>();
    res[kBuildFarmId] = { std::make_pair(kEffortId, -50), std::make_pair(kFarmId, 1) };
    res[kFarmFoodId] = { std::make_pair(kEffortId, -20), std::make_pair(kFoodId, 10) };
    res[kScavengeId] = { std::make_pair(kEffortId, -10), std::make_pair(kRandomProductId, 1) };
    res[kReproductionId] = { std::make_pair(kEffortId, -100), std::make_pair(kFamilyMemberId, 1) };
    return res;
}