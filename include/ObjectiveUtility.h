#pragma once

class ObjectiveUtility
{
public:
	ObjectiveUtility() = default;
	ObjectiveUtility(float max, int optimal, int useless, int harmfull);
	float GetMarginalUtility(int owned, int number) const;
	float GetTotalUtility(int number) const;
private:
	const float mMax = 0.0f;
	const int mOptimal = 0;
	const int mUseless = 0;
    const int mHarmfull = 0;
};
