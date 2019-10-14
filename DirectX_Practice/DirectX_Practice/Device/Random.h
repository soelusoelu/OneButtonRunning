#pragma once

#include <random>

class Random {
public:
    Random();
    ~Random();
    static unsigned random();
    static int randomRange(int min, int max);
    static float randomRange(float min, float max);

private:
    static std::mt19937 mt;
};

