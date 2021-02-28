#pragma once
#include <stdint.h>

class ObjectiveUtility
{
public:
	ObjectiveUtility() = default;
	~ObjectiveUtility() = default;
	ObjectiveUtility(float max, int32_t optimal, int32_t useless, int32_t harmfull);
	float GetMarginalUtility(int32_t owned, int32_t number) const;
	float GetTotalUtility(int32_t number) const;
private:
	const float mMax = 0.0f;
	const int32_t mOptimal = 0;
	const int32_t mUseless = 0;
	const int32_t mHarmfull = 0;
};
