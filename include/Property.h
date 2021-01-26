#pragma once

#include <memory>

class Owner;

class Property: public std::enable_shared_from_this<Property>
{
public:
    Owner* GetOwner() const;
    void SetOwner(std::shared_ptr<Owner> person);
private:
    std::weak_ptr<Owner> mOwner;
};