#pragma once
#include <memory>

class Food;
using FoodSP = std::shared_ptr<Food>;
using FoodWP = std::weak_ptr<Food>;

class Person;
using PersonSP = std::shared_ptr<Person>;
using PersonWP = std::weak_ptr<Person>;

class Farm;
using BuildingSP = std::shared_ptr<Farm>;
using BuildingWP = std::weak_ptr<Farm>;