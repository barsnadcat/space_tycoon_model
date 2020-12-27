#include <ProductionsConfig.h>

std::map<ProductionId, std::vector<ProductionConfig>> GetProductions()
{
    auto res = std::map<ProductionId, std::vector<ProductionConfig>>();
    res[kBuildFarmId] = { {kEffortId, -50, false}, {kFarmId, 1, false} };
    res[kFarmFoodId] = { {kEffortId, -20, false}, {kFarmId, -1, true}, {kFoodId, 10, false} };
    res[kScavengeId] = { {kEffortId, -10, false}, {kRandomProductId, 1, false} };
    res[kReproductionId] = { {kEffortId, -100, false}, {kFamilyMemberId, 1, false} };
    return res;
}