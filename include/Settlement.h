#pragma once

#include <Space.h>

class Settlement: public Space
{
public:
    Settlement(size_t landSize): Space(landSize) {}
};
