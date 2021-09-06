#pragma once


template<typename T>
T lowtoHigh(int n)
{
	T accum = static_cast<T>(0);
	for (int i = 1; i <= n; ++i)
	{
		accum += pow(static_cast<T>(-1), static_cast<T>(i)) / static_cast<T>(i);
	}
	return accum;
}
template<typename T>
T highToLow(int n)
{
	T accum = static_cast<T>(0);
	for (int i = n; i >= 1; --i)
	{
		accum += pow(static_cast<T>(-1), static_cast<T>(i)) / static_cast<T>(i);
	}
	return accum;
}
template<typename T>
T lowtoHighSeparate(int n)
{
	T negative = static_cast<T>(0);
	T positive = static_cast<T>(0);
	for (int i = 1; i <= n; ++i)
	{
		T value = pow(static_cast<T>(-1), static_cast<T>(i)) / static_cast<T>(i);
		if (value < 0)
			negative += value;
		else
			positive += value;
	}
	return negative + positive;
}
template<typename T>
T highToLowSeparate(int n)
{
	T negative = static_cast<T>(0);
	T positive = static_cast<T>(0);
	for (int i = n; i >= 1; --i)
	{
		T value = pow(static_cast<T>(-1), static_cast<T>(i)) / static_cast<T>(i);
		if (value < 0)
			negative += value;
		else
			positive += value;
	}
	return negative + positive;
}
template<typename T>
void computeSumm()
{
	std::cout << "Direct sum: " << std::fixed << std::setprecision(std::numeric_limits<T>::max_digits10) << lowtoHigh<T>(10000) << "\n";
	std::cout << "Reverse sum: " << highToLow<T>(10000) << "\n";
	std::cout << "Low to high separate sum: " << lowtoHighSeparate<T>(10000) << "\n";
	std::cout << "High to low separate sum: " << highToLowSeparate<T>(10000) << "\n";
}