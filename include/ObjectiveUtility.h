#pragma once

class ObjectiveUtility
{
public:
	ObjectiveUtility(int optimal, int useless, int harmfull);
	float GetMarginalUtility(int owned, int number) const; // never returns higher that 1.0
	float GetTotalUtility(int number) const; // never returns higher that 1.0
private:
	const int mOptimal = 0;
	const int mUseless = 0;
    const int mHarmfull = 0;
};
