#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include <string>
#include <algorithm>

#define DATABASE_FILE "data.csv"
#define DEBUG_DATABASE 1
#define DEBUG_SHOW_DATABASE 1

int	storeDatabase(std::string fileName, std::map<std::string, std::string> &databaseToFill, char separator)
{
	std::ifstream inputFile(fileName.c_str());
	if (inputFile)
	{
		char	buffer1[256];
		char	buffer2[256];
		int		dateFirst = 0;

		inputFile.getline(buffer1, 256, separator);
		inputFile.getline(buffer2, 256);
#if DEBUG_DATABASE
		std::cout << "first line, first word: " << buffer1 << std::endl;
		std::cout << "first line, second word: " << buffer2 << std::endl;
#endif
		if (strncmp("date", buffer1, 4) == 0)
		{
			dateFirst = 1;
			std::cout << "database is date first" << std::endl;
		}
		else if (strncmp("date", buffer2, 4) != 0 || strncmp(" date", buffer2, 5) != 0)
		{
			std::cout << "database is date second" << std::endl;
			return (1);
		}
		while (inputFile.getline(buffer1, 256, ','))
		{
			inputFile.getline(buffer2, 256);
			if (dateFirst)
			{
				databaseToFill.insert(std::make_pair(buffer1, buffer2));
				std::cout << "filling database as date first" << std::endl;
			}
			else
			{
				databaseToFill.insert(std::make_pair(buffer2, buffer1));
				std::cout << "filling database as date second" << std::endl;
			}
		}
#if DEBUG_SHOW_DATABASE
		for (std::map<std::string, std::string>::iterator it = databaseToFill.begin();
				it != databaseToFill.end(); it++)
			std::cout << "Database_key: " << it->first << " database_value: " << it->second << std::endl;
#endif
	}
	else
	{
		std::cout << "Invalid database file" << std::endl;
	}
	return (0);
}

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

	if (argc != 2)
	{
		std::cout << "Please provide database file" << std::endl;
		return (0);
	}
	if (storeDatabase("data.csv", bitcoinDatabase, ','))
	{
		std::cerr << "Error in database" << std::endl;
		return (0);
	}
	storeDatabase(argv[1], comparisonDatabase, '|');
	compareDatabases(bitcoinDatabase, comparisonDatabase);
	return (0);
}
