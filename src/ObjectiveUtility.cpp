#include <ObjectiveUtility.h>
#include <easylogging++.h>

ObjectiveUtility::ObjectiveUtility(float max, int optimal, int useless, int harmfull): mMax(max), mOptimal(optimal), mUseless(useless), mHarmfull(harmfull)
{
	if (max <= 0)
	{
		LOG(ERROR) << "max(" << max << ") should be greater than zero!";
	}

	if (optimal >= useless)
	{
		LOG(ERROR) << "optimal(" << optimal << ") >= useless (" << useless << ")";
	}

	if (useless >= harmfull)
	{
		LOG(ERROR) << "useless(" << useless << ") >= harmfull (" << harmfull << ")";
	}
}

float ObjectiveUtility::GetTotalUtility(int number) const
{
	if (number < mOptimal)
	{
		float utilityPerUnit = mMax / mOptimal;
		return number * utilityPerUnit;
	}

	if (number > mUseless)
	{
		float utilityPerUnit = mMax / (mHarmfull - mUseless);
		return mMax - (number - mUseless) * utilityPerUnit;
	}
	else
	{
		return mMax;
	}
}

float ObjectiveUtility::GetMarginalUtility(int owned, int number) const
{
	return GetTotalUtility(owned + number) - GetTotalUtility(owned);
}
