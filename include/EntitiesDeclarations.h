#pragma once
#include <memory>
#include <vector>

using ProductId = std::size_t;
const ProductId kFoodId = std::hash<std::string>{}("Food");
const ProductId kFarmId = std::hash<std::string>{}("Farm");
using ProductionId = std::size_t;
const ProductionId kBuildFarmId = std::hash<std::string>{}("BuildFarm");
const ProductionId kFarmFoodId = std::hash<std::string>{}("FarmFood");
const ProductionId kScavengeId = std::hash<std::string>{}("Scavenge");

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