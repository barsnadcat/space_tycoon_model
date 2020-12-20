#pragma once
#include <map>
#include <vector>
#include <EntitiesDeclarations.h>

std::map<ProductionId, std::vector<std::pair<ProductId, int32_t>>> GetProductions();
