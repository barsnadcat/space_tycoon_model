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

class Entity;
using EntitySP = std::shared_ptr<Entity>;
using EntityWP = std::weak_ptr<Entity>;
using EntitySPs = std::vector<EntitySP>;
using EntityWPs = std::vector<EntityWP>;

class Food;
using FoodSP = std::shared_ptr<Food>;
using FoodWP = std::weak_ptr<Food>;

class Person;
using PersonSP = std::shared_ptr<Person>;
using PersonWP = std::weak_ptr<Person>;

class Farm;
using FarmSP = std::shared_ptr<Farm>;
using FarmWP = std::weak_ptr<Farm>;