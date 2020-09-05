#pragma once
#include <random>
#include <cstdint>

struct UpdateContext
{
    UpdateContext(int seed = 1)
    {
        mRandomEngine.seed(seed);
    }
    uint32_t mCurrentTime { 0 };
    std::mt19937 mRandomEngine;
};