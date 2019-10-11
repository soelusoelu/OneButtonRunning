#pragma once

#include <random>

class Random {
public:
    Random();
    ~Random();
    int random();
    int randomRange(int min, int max);
    float randomRange(float min, float max);

private:
    std::mt19937 mt;
};

