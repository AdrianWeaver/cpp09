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

int	checkDate(std::string date)
{
	std::cout << "Atoi: " << atoi(date.c_str()) << std::endl;
	return (0);
}

void	compareDatabases(std::map<std::string, std::string> &bitcoinDatabase, std::map<std::string, std::string> &comparisonDatabase)
{
	for (std::map<std::string, std::string>::iterator it = comparisonDatabase.begin();
			it != comparisonDatabase.end(); it++)
	{
		if (checkDate(it->first) == 0)
		{
			std::map<std::string, std::string>::iterator found;
			found = bitcoinDatabase.find(it->first);
			if (found != bitcoinDatabase.end())
				std::cout << "On " << it->first << " " << it->second << " was worth " << found->second << " dollars." << std::endl;
			else
			{
				found = bitcoinDatabase.lower_bound(it->first);
				std::cout << "On " << found->first << " closest date to " << it->first << " stored in database " << it->second << " was worth " << found->second << " dollars." << std::endl;
			}
		}
		else
			std::cout << it->first << " is not a valid date." << std::endl;
	}
}

int	main(int argc, char **argv)
{
	std::map<std::string, std::string> bitcoinDatabase;
	std::map<std::string, std::string> comparisonDatabase;

	(void)argv;
	if (argc != 2)
	{
		std::cout << "Please provide database file" << std::endl;
		return (0);
	}

	try
	{
		Database bitcoin("data.csv");
		//storeDatabase(argv[1], comparisonDatabase, '|');
		compareDatabases(bitcoinDatabase, comparisonDatabase);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
