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

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "Error, no values provided." << std::endl;
		return (0);
	}
	try
	{
		std::cout << "argc = " << argc << std::endl;
		PmergeMe	sorted(argc, argv);
		//sorted.printVectorStorage();
		sorted.updateTimer();
		sorted.sort();
		if (sorted.isVectorStorageSorted())
			std::cout << "Vector is sorted" << std::endl;
		else
			std::cout << "VECTOR IS NOT SORTED" << std::endl;

		//sorted.printVectorStorage();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
