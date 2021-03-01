#include <ProductionsConfig.h>

std::map<ProductionId, std::vector<ProductionConfig>> GetProductions()
{
    auto res = std::map<ProductionId, std::vector<ProductionConfig>>();
    res[kBuildFarmId] = { {kEffortId, -50, false}, {kFarmId, 1, false} };
    res[kFarmFoodId] = { {kEffortId, -2, false}, {kFarmId, -1, true}, {kFoodId, 10, false} };
    res[kScavengeId] = { {kEffortId, -1, false}, {kRandomProductId, 1, false} };
    res[kReproductionId] = { {kEffortId, -150, false}, {kPersonId, 1, false} };
    return res;
}