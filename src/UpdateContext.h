#pragma once
#include <random>

struct UpdateContext
{
    UpdateContext(int seed = 1)
    {
        mRandomEngine.seed(seed);
    }
    std::default_random_engine mRandomEngine;
};