#pragma once
#include <memory>

class Food;
using FoodSP = std::shared_ptr<Food>;
using FoodWP = std::weak_ptr<Food>;

class Person;
using PersonSP = std::shared_ptr<Person>;
using PersonWP = std::weak_ptr<Person>;

class Building;
using BuildingSP = std::shared_ptr<Building>;
using BuildingWP = std::weak_ptr<Building>;