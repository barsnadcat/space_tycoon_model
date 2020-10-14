#pragma once

#include <memory>

class Person;

class Property
{
public:
    Person* GetOwner();
private:
    std::weak_ptr<Person> mOwner;
};