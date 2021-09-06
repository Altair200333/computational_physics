#pragma once
#include <bitset>

//https://www.h-schmidt.net/FloatConverter/IEEE754.html

template <typename T>
bool isSubnormal(T value)
{
	return true;
}

template <>
bool isSubnormal(float value)
{
	constexpr uint8_t size = sizeof(float) * 8;
	std::bitset<size>* bits = reinterpret_cast<std::bitset<size>*>(&value);
	for (int i = 23; i <= 30; ++i)
	{
		if ((*bits)[i] != 0)
			return false;
	}
	return true;
}

template <>
bool isSubnormal(double value)
{
	constexpr uint8_t size = sizeof(double) * 8;

	std::bitset<size>* bits = reinterpret_cast<std::bitset<size>*>(&value);
	for (int i = 52; i <= 62; ++i)
	{
		if ((*bits)[i] != 0)
			return false;
	}
	return true;
}

