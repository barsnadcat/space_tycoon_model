#pragma once
#include <memory>
#include <vector>

using ProductId = std::size_t;
const ProductId kInvalidId = 0;
const ProductId kFoodId = 1;
const ProductId kFarmId = 2;
const ProductId kEffortId = 3;
const ProductId kFamilyMemberId = 4;
const ProductId kRandomProductId = 5;

using ProductionId = std::size_t;
const ProductionId kBuildFarmId = 1;
const ProductionId kFarmFoodId = 2;
const ProductionId kScavengeId = 3;
const ProductionId kReproductionId = 4;

class Food;
class Person;
class Farm;

class Object;
using ObjectSP = std::shared_ptr<Object>;
using ObjectWP = std::weak_ptr<Object>;
using ObjectSPs = std::vector<ObjectSP>;
using ObjectWPs = std::vector<ObjectWP>;
