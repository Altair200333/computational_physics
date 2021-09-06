#pragma once
#include <iostream>

typedef union
{
    float f;
    struct
	{
        unsigned int mantisa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } parts;
} FloatRepresentation;

void printValueRepresentation(float value)
{
    FloatRepresentation d1 = { d1.f = 0.15625 };
    std::cout << d1.parts.sign<< " "<< d1.parts.exponent<<" "<< d1.parts.mantisa;
    
    std::cout << "\n";
}

template<typename T>
int getMantissaPrecision()
{
    int decimalPlace = 1;
	
    while (static_cast<T>(1) + static_cast<T>(std::pow(static_cast<T>(10), static_cast<T>(-1*decimalPlace))) != static_cast<T>(1))
    {
        ++decimalPlace;
    }
    return decimalPlace;
}

template<typename T>
int maxExp10()
{
    int maxPow = 1;
    T previous = static_cast<T>(0);
    while (true)
    {
        T value = static_cast<T>(pow(static_cast<T>(10), static_cast<T>(maxPow)));

    	//перед тем как выйти, без последней проверки value дважды вылетит в inf
        if (value <= previous || isinf(value))
            return maxPow - 1;
        previous = value;
        ++maxPow;
    }
}

template<typename T>
int minExp10()
{
    int minPow = -1;
    T previous = static_cast<T>(1);
    while (true)
    {
        T value = static_cast<T>(pow(static_cast<T>(10), static_cast<T>(minPow)));
    	
        if (value >= previous || (value <= std::numeric_limits<T>::min()))
            return minPow + 1;
    	
        previous = value;
        --minPow;
    }
}
template<typename T>
void printPrecisions()
{
    std::cout << "Mantissa decimal places: "<< getMantissaPrecision<T>() << "\n";
    std::cout << "Max10 power: "<< maxExp10<T>()<<"; expected: "<< std::numeric_limits<T>::max_exponent10 << "\n";
    std::cout << "Min10 power: "<< minExp10<T>()<<"; expected: "<< std::numeric_limits<T>::min_exponent10 << "\n";
}