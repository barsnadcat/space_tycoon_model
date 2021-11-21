#pragma once

#include <Entity.h>
#include <vector>
#include <memory>

class Land;
class Person;

class Farm: public Entity
{
public:
	Farm(Entity* prev, uint32_t health);
	virtual ~Farm();

	void SetLand(Land* land){ mLand = land; }
	Land* GetLand() const { return mLand; }
	Person* GetPerson() const { return mPerson; }
	void SetPerson(Person* p) { mPerson = p; }

private:
	Land* mLand = nullptr;
	Person* mPerson = nullptr;
};
