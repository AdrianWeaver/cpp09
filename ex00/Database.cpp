#include "Database.hpp"

Database::Database()
{
}

Database::~Database()
{
}

Database::Database(const Database &source)
{
	*this = source;
}

Database &Database::operator=(const Database &rhs)
{
	(void)rhs;
	return (*this);
}

Database::Database(std::string fileName)
{
	std::ifstream inputFile(fileName.c_str());
	if (inputFile)
	{
		/* previous way of doing it */
		char	buffer1[256];
		char	buffer2[256];
		int		dateFirst = 0;

		inputFile.getline(buffer1, 256, ',');
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
		else if (strncmp("date", buffer2, 4) == 0 || strncmp(" date", buffer2, 5) == 0)
			std::cout << "database is date second" << std::endl;
		else
			throw Database::InvalidDatabaseException();
		while (inputFile)
		{
			int year = 0, month = 0, day = 0;
			int date = 0;
			char div1 = 0, div2 = 0, div3 = 0;
			float value = 0;
			if (dateFirst)
				inputFile >> year >> div1 >> month >> div2 >> day >> div3 >> value;
			else
				inputFile >> value >> div3 >> year >> div1 >> month >> div2 >> day;
			if (dateIsCorrect(year, month, day) && div1 == '-' && div2 == div1)
			{
				date = (year << 9) | (month << 5) | day;
					this->_storage.insert(std::make_pair(date, value));
			}
		}
//#if DEBUG_SHOW_DATABASE
		for (std::map<int, float>::iterator it = this->_storage.begin();
				it != this->_storage.end(); it++)
			std::cout << "Database_key: " << (it->first >> 9) << "/" <<
				((it->first >> 5) & 0b1111) << "/" <<
				(it->first & 0b11111) << " database_value: " << it->second << std::endl;
//#endif
	}
	else
		throw Database::InvalidFileException();
}

const char *Database::InvalidDatabaseException::what() const throw()
{
	return ("Database format is invalid\n");
}
const char *Database::InvalidFileException::what() const throw()
{
	return ("Invalid file\n");
}

int	Database::dateIsCorrect(int year, int month, int day)
{
	int leapYear = 0;
	if (year % 400 == 0 || ((year % 4) == 0 && (year % 100) != 0))
		leapYear = 1;
	if (year < 2004 || year > 2024)
		return (0);
	if (month < 1 || month > 12)
		return (0);
	if (day > 31 || day < 1)
		return (0);
	if (leapYear && month == 2 && day <= 29)
		return (1);
	if (month % 2 == 0 && day >= 31)
		return (0);
	return (1);
}

void	Database::compare(Database &toCompare)
{
	for (std::map<int, float>::iterator focus = toCompare._storage.begin();
			focus != toCompare._storage.end(); focus++)
	{
		if (focus->second > 0 && focus->second < 1000)
		{
			std::map<int, float>::iterator found = this->_storage.lower_bound(focus->first);
			if (found->first != focus->first && found != this->_storage.begin())
				found--;
			std::cout << "Value on " << (focus->first >> 9) << "/" <<
			std::setw(2) << std::setfill('0') << ((focus->first >> 5) & 0b1111) << "/" <<
			std::setw(2) << std::setfill('0') << (focus->first & 0b11111);
			std::cout << " for " << focus->second << " btc was " << std::fixed << std::setprecision(2) << focus->second * found->second << " euros." << std::endl;

		}
	}
}

void	Database::compareFile(std::string fileName)
{
	std::ifstream inputFile(fileName.c_str());
	if (inputFile)
	{
		std::string	buffer;

		getline(inputFile, buffer);
		if (buffer != "date | value")
			throw Database::InvalidDatabaseException();
		while (!inputFile.eof())
		{
			int year = 0, month = 0, day = 0;
			int date = 0;
			char div1 = 0, div2 = 0, div3 = 0;
			float value = 0;
			inputFile >> year >> div1 >> month >> div2 >> day >> div3 >> value;
			std::cout << "year:" << year << std::endl
				<< "div1:" << div1 << std::endl
				<< "month:" << month << std::endl
				<< "div2:" << div2 << std::endl
				<< "day:" << day << std::endl
				<< "div3:" << div3 << std::endl
				<< "value:" << value << std::endl;
			if (dateIsCorrect(year, month, day) && div1 == '-' && div2 == div1)
			{
				if (value < 0)
					std::cerr << "Error: not a positive number" << std::endl;
				if (inputFile.fail())
				{
					inputFile.clear();
					std::cout << "entered here fail bit" << std::endl;
					std::string wesh;
					getline(inputFile, wesh);

					std::cout << "[" << wesh << "]" << std::endl;;
				}
				else if (value > 0 && value <= 1000)
				{
					date = (year << 9) | (month << 5) | day;
					std::map<int, float>::iterator found;
					found = this->_storage.lower_bound(date);
					if (found->first != date && found != this->_storage.begin())
						found--;
					std::cout << "Value on " << (date >> 9) << "/" <<
						std::setw(2) << std::setfill('0') << ((date >> 5) & 0b1111) << "/" <<
						std::setw(2) << std::setfill('0') << (date & 0b11111);
					std::cout << " for " << value << " btc was " << std::fixed << std::setprecision(2) << value * found->second << " euros." << std::endl;
				}
				else
					std::cout << "Error invalid value given" << std::endl;
			}
			else
				std::cout << "Error: invalid date" << std::endl;
		}
		std::cout << "error in the file" << std::endl;
	}
	else
		throw Database::InvalidFileException();
}







