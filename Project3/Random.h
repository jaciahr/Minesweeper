#pragma once
#include <random>
class Random
{
    static std::mt19937 random;
public:
    //static int x;
    //int y, z;
    //One and only one of this function
    static int Int(int min, int max);
    //One value shared among all objects of this class?
    //Value belongs to the class, not just one instance of the class
    //All instances share this variable
    //Can't have copies/duplicates
    //Static variables/functions exists for the lifetime of your program
    //Similar to global variables? Static better though, more formal than the junk drawer of global
    //Can make a static variable private

    static float Float(float min, float max);
    //Inside a static function, we cannot access non-static items like y
    //"this" doesn't exist
    //non-static functions can use static variables?
};