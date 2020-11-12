#include <ObjectiveUtility.h>
#include <easylogging++.h>

ObjectiveUtility::ObjectiveUtility(int optimal, int useless, int harmfull): mOptimal(optimal), mUseless(useless), mHarmfull(harmfull)
{
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
        float utilityPerUnit = 1.0f / mOptimal;
        return number * utilityPerUnit;
    }

    if (number > mUseless)
    {
        float utilityPerUnit = 1.0f / (mHarmfull - mUseless);
        return 1.0f - (number - mUseless) * utilityPerUnit;        
    }
    else
    {
        return 1.0f;        
    }    
}

float ObjectiveUtility::GetMarginalUtility(int owned, int number) const
{
    return GetTotalUtility(owned + number) - GetTotalUtility(owned);
}