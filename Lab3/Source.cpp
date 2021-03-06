#include "P8dot2.h"
#include "P9dot2.h"
#include "P9dot3.h"
#include <iostream>

int main()
{
	std::cout << "P8.2:" << std::endl;

	P8dot2::run();

	std::cout << std::endl << std::endl;

	std::cout << "P9.2:" << std::endl;

	P9dot2::run();

	std::cout << std::endl << std::endl;

	std::cout << "P9.3:" << std::endl;

	P9dot3::run();

	return 0;
}