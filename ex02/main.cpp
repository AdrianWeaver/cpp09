#include "PmergeMe.hpp"

#include <algorithm>
#include <list>
#include <vector>

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#define EVALUATION_HELPER 0

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "Error, no values provided." << std::endl;
		return (0);
	}
	try
	{
		PmergeMe	sorted(argc, argv);
		std::cout << "Before: ";
		sorted.printVectorStorage();
		sorted.sort();
		std::cout << "After: ";
		sorted.printVectorStorage();
		sorted.printTimers();
#if EVALUATION_HELPER
		if (sorted.isVectorStorageSorted())
			std::cout << "Vector is sorted" << std::endl;
		else
			std::cout << "VECTOR IS NOT SORTED" << std::endl;
#endif

	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
