#include "RPN.hpp"

int main(int argc, char **argv)
{
	try
	{
		for (int i = 1; i < argc; i++)
		{
			RPN	data(argv[i]);
			std::cout << data.getTopValue() << std::endl;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Abort: " << e.what() << std::endl;
	}
	return (0);
}
