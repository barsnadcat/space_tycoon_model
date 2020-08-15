#pragma once
#include <random>

struct UpdateContext
{
    UpdateContext(int seed = 1)
    {
        mRandomEngine.seed(seed);
    }
    std::mt19937 mRandomEngine;
};