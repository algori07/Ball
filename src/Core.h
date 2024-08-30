#pragma once

#include <utility>
#include <cmath>

#include <cstdlib>
#include <ctime>

// Return a pair, first value is less or equal than second value
// If first value is greater than second value, there's no value
// of x
std::pair<double, double> findXInQuadraticEquation(double a, double b, double c)
{
    if(a == 0) return {
        (double)(-c)/b,
        (double)(-c)/b};

    long double delta = b*b - 4*a*c;
    
    if(delta<0) return {1,0};
    else if(delta == 0)
    {
        int ans = (double)(-b)/2/a;
        return {ans,ans};
    }
    else if(a > 0) return {
        (double)(-b - std::sqrt(delta))/2/a,
        (double)(-b + std::sqrt(delta))/2/a};
    else return {
        (double)(-b + std::sqrt(delta))/2/a,
        (double)(-b - std::sqrt(delta))/2/a};
    return {1,0};
}

int randint(int start, int end)
{
    return rand() % (end - start + 1) + start;
}