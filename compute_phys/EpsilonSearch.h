#pragma once
#include <functional>
#include <iostream>
#include "subnormal.h"

template<typename T>
struct EpsilonSearchResult
{
    T eps;

    bool found;
    uint32_t steps;

    EpsilonSearchResult(T _eps, bool _found, uint32_t _steps) : eps(_eps), found(_found), steps(_steps)
    {
    }
};

template<typename T>
bool compareEpsilon(T eps)
{
    return (static_cast<T>(1.0) + eps * static_cast<T>(0.5) == static_cast<T>(1.0)) && (static_cast<T>(1.0) + eps != static_cast<T>(1.0));
}

template<typename T>
EpsilonSearchResult<T> findMachineEpsilon(T left, T right, std::function<bool(T)> epsilonCondition)
{
    T epsilon = (left + right) * static_cast<T>(0.5);

    uint32_t searchSteps = 0;

    while (true)
    {
        if (left == epsilon || right == epsilon)
            break;

        searchSteps++;

        const bool halfEpsilonIsOne = (static_cast<T>(1.0) + epsilon * static_cast<T>(0.5)) == static_cast<T>(1.0);

        if (halfEpsilonIsOne || isSubnormal(epsilon))//малое число
        {
            left = epsilon;
        }
        else if (!halfEpsilonIsOne)//слишком много
        {
            right = epsilon;
        }
       
        //в любом случае пытайся найти eps посередине
        epsilon = (left + right) * static_cast<T>(0.5);
    }

    return EpsilonSearchResult<T>(epsilon, epsilonCondition(epsilon), searchSteps);
}

template<typename T>
struct ComparedValue
{
    T value;
	std:: string name;
};
template<typename T>
void findEpsilonAndCompare()
{
    const auto eps = findMachineEpsilon<T>(static_cast<T>(0.0), static_cast<T>(1.0), compareEpsilon<T>);

    constexpr auto realEpsilon = std::numeric_limits<T>::epsilon();
    std::cout << std::scientific << eps.eps << "; expected: " << realEpsilon << " " << std::boolalpha << eps.found << "; steps: " << eps.steps << "\n";
    std::cout << std::noboolalpha;

    std::cout << "\n";
    
    ComparedValue<T> values[] = 
    {
    	{static_cast<T>(1.0),                                           "1          "},
    	{static_cast<T>(1.0) + eps.eps * static_cast<T>(0.5),           "1 + e/2    "},
    	{static_cast<T>(1.0) + eps.eps,                                 "1 + e      "},
    	{static_cast<T>(1.0) + eps.eps + eps.eps * static_cast<T>(0.5), "1 + e + e/2"},
    };
    for (int i = 0; i < 4; ++i)
    {
        std::cout << values[i].name << "-- ";
        std::cout << std::fixed << std::setprecision(std::numeric_limits<T>::max_digits10) << values[i].value << "\n";
    }
	for (int i=0;i<4;++i)
	{
        std::cout << values[i].name << "-- ";
        for (int j = 0; j < 4; ++j)
        {
            std::cout << (values[i].value == values[j].value) << " ";
        }
        std::cout << "\n";
	}
}