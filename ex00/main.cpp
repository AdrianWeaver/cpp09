#include <iostream>
#include <fstream>
#include <map>

#define DATABASE_FILE "data.csv"
//int isValidDate(std::fstream RawKey)
//{

//}
void	storeDatabase(std::map<std::string, std::string> &bitcoinDatabase)
{
	std::ifstream inputFile(DATABASE_FILE);
	if (inputFile)
	{
		char buffer1[256];
		char buffer2[256];
		inputFile.getline(buffer1, 256);
		while (inputFile.getline(buffer1, 256, ','))
		{
			inputFile.getline(buffer2, 256);
			bitcoinDatabase.insert(std::make_pair(buffer1, buffer2));
		}
	}
	else
	{
		std::cout << "Invalid database file" << std::endl;
	}
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

	if (argc != 2)
	{
		std::cout << "Please provide database file" << std::endl;
		return (0);
	}
	storeDatabase(bitcoinDatabase);
	compareWithFile(argv[1], bitcoinDatabase);
	return (0);
}
