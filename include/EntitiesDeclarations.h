#pragma once

#include <cstddef>

using ObjectId = std::size_t;
const ObjectId kInvalidId = 0;
const ObjectId kFoodId = 1;
const ObjectId kFarmId = 2;
const ObjectId kEffortId = 3;
const ObjectId kPersonId = 4;
const ObjectId kRandomProductId = 5;
const ObjectId kSettlementId = 6;

using ProductionId = std::size_t;
const ProductionId kBuildFarmId = 1;
const ProductionId kFarmFoodId = 2;
const ProductionId kScavengeId = 3;
const ProductionId kReproductionId = 4;
