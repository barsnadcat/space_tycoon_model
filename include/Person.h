#pragma once

#include <EntitiesDeclarations.h>
#include <Object.h>

#include <map>

class Space;

std::map<ObjectId, float> Mutate(UpdateContext& uc, std::map<ObjectId, float>);
std::map<ObjectId, float> RandomPreferences(UpdateContext& uc);

class Person
{
public:
	Person(Object& thisObject, int32_t energy, const std::map<ObjectId, float>& preferences):
		mThisObject(thisObject), mEnergy(energy), mPreferences(preferences) {}
	void Update(UpdateContext& uc);
	ProductionId GetBestProduction(UpdateContext& uc) const;
	void Produce(UpdateContext& uc, Object& workSpace, ProductionId productionId);
private:
	float GetMarginalUtility(UpdateContext& uc, ObjectId productId, int32_t number) const;
	float GetPersonalPreference(ObjectId) const;
	float GetProductionValue(UpdateContext& uc, ProductionId productionId) const;
	bool CanDoProduction(UpdateContext& uc, ProductionId productionId) const;
	int32_t GetPersonOwned(ObjectId productId) const;
	void Scavenge(Object& workSpace);
	void Reproduce(UpdateContext& uc, Object& workSpace);
private:
	Object& mThisObject;
	int32_t mEnergy = 0;
	int32_t mChildren = 0;
	std::map<ObjectId, float> mPreferences;
};

ObjectSP ConstructPerson(uint32_t health, int32_t energy, const std::map<ObjectId, float>& preferences);
