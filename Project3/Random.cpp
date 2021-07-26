#include "Random.h"
#include <ctime>

std::mt19937 Random::random(time(0));
//int Random::x = 100;

//Don't have to use static if you already mentioned it in the header
int Random::Int(int min, int max) {
    //When dealing with static variables, they must be redeclared in global space
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random);
}

float Random::Float(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(random);
}