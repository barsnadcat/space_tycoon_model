#pragma once

#include <Entity.h>

class Land;
class Person;

class Food: public Entity
{
public:
	Food(Entity* prev, uint32_t health):
		Entity(prev, health, 1){}
	virtual ~Food();
	int32_t GetEnergy() const { return 3; }

	void SetLand(Land* pLand) { mLand = pLand; }
	Land* GetLand() const { return mLand; }
	Person* GetPerson() const { return mPerson; }
	void SetPerson(Person* p) { mPerson = p; }

private:
	Land* mLand = nullptr;
	Person* mPerson = nullptr;
};
