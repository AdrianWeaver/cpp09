#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include <string>
#include <algorithm>
#include "Database.hpp"

#define DATABASE_FILE "data.csv"
#define DEBUG_DATABASE 1
#define DEBUG_SHOW_DATABASE 1

void	compareWithFile(char *fileName, std::map<std::string, std::string> &bitcoinDatabase)
{
	std::ifstream compareFile(fileName);
	if (compareFile)
	{
		char buffer[256];
		while (compareFile.getline(buffer, 256, '\n'))
		{
			std::map<std::string, std::string>::iterator found;
			found = bitcoinDatabase.find(buffer);
			if (found != bitcoinDatabase.end())
				std::cout << "bitcoin value at " << buffer << " was : " << found->second << std::endl;
			else
			{
				found = bitcoinDatabase.lower_bound(buffer);
				std::cerr << "No correspondance in database for \"" << buffer << "\" please check date format YYYY-MM-DD" <<
					std::endl << "valid dates between 2009-01-02 and 2022-03-39" << std::endl;
			}
		}
	}
	else
		std::cout << "Invalid comparision file, aborting." << std::endl;
}

int	main(int argc, char **argv)
{
	std::map<std::string, std::string> bitcoinDatabase;
	std::map<std::string, std::string> comparisonDatabase;

	if (argc != 2)
	{
		std::cout << "Please provide database file" << std::endl;
		return (0);
	}

	try
	{
		Database bitcoin("data.csv");
		bitcoin.compareFile(argv[1]);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
