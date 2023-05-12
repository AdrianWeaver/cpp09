#include <iostream>
#include <fstream>
#include <map>

//int isValidDate(std::fstream RawKey)
//{

//}
void	storeDatabase(char *fileName, std::map<std::string, std::string> &bitcoinDatabase)
{
	std::ifstream inputFile(fileName);
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
		for (std::map<std::string, std::string>::iterator it = bitcoinDatabase.begin(); it != bitcoinDatabase.end(); it++)
			std::cout << it->first << " = " << it->second << std::endl;
	}
	else
	{
		std::cout << "Invalid database file" << std::endl;
	}
}

int	main(int argc, char **argv)
{
	std::map<std::string, std::string> bitcoinDatabase;

	if (argc != 2)
	{
		std::cout << "Please provide database file" << std::endl;
		return (0);
	}
	storeDatabase(argv[1], bitcoinDatabase);
	return (0);
}
