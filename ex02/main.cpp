#include "PmergeMe.hpp"

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
		sorted.updateTimer();
		std::cout << "Timer at the end: " << sorted.getTimer() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
