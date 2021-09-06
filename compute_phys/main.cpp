#include <functional>
#include <iostream>
#include <iomanip>
#include  <bitset>

#include "DecimalStudy.h"
#include "EpsilonSearch.h"
#include "InspectSum.h"


template <typename T>
void hackyMinNumber()
{
	std::bitset<sizeof(T) * 8> bits;
	bits.set(0, 1);

	T* value = reinterpret_cast<T*>(&bits);
	std::cout << "Manually set first bit: " << *value << "\n";
	std::cout << "Minimum subnormal value (std): " << std::numeric_limits<T>::denorm_min() << "\n";
	std::cout << "\n";
}

void printMachineEpsilon()
{
	std::cout << "float: \n";
	findEpsilonAndCompare<float>();
	std::cout << "\n";
	printPrecisions<float>();

	std::cout << "\n";

	std::cout << "double: \n";
	findEpsilonAndCompare<double>();
	std::cout << "\n";
	printPrecisions<double>();
}

void printBigSumm()
{
	std::cout << "\n";
	computeSumm<float>();

	std::cout << "\n";
	computeSumm<double>();
}

int main()
{
	hackyMinNumber<float>();
	hackyMinNumber<double>();

	printMachineEpsilon();

	printBigSumm();

	return 0;
}
