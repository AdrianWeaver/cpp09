#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &source)
{
	*this = source;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	(void)rhs;
	return (*this);
}

BitcoinExchange::BitcoinExchange(std::string fileName)
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
		if (strncmp("date", buffer1, 4) == 0)
			dateFirst = 1;
		else if (strncmp("date", buffer2, 4) == 0 || strncmp(" date", buffer2, 5) == 0)
			dateFirst = 0;
		else
			throw BitcoinExchange::InvalidDatabaseException();
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
#if DEBUG_SHOW_DATABASE
		for (std::map<int, float>::iterator it = this->_storage.begin();
				it != this->_storage.end(); it++)
			std::cout << "Database_key: " << (it->first >> 9) << "/" <<
				((it->first >> 5) & 0b1111) << "/" <<
				(it->first & 0b11111) << " database_value: " << it->second << std::endl;
#endif
	}
	else
		throw BitcoinExchange::InvalidFileException();
}

void	BitcoinExchange::printExactValue(int date, float value, float btcRate)
{
	std::cout << "[" << (date >> 9) << "/"
		<< std::setw(2) << std::setfill('0') << ((date >> 5) & 0b1111)
		<< "/" << std::setw(2) << std::setfill('0') << (date & 0b11111) << "] ";
		std::cout << value << " btc == "
		<< std::fixed << std::setprecision(2) << value * btcRate << " euros." << std::endl;
}

void	BitcoinExchange::printApproxValue(int realDate, int closestDate, float value, float btcRate)
{
	std::cout << "No ref for [" << (realDate >> 9) << "/"
		<< std::setw(2) << std::setfill('0') << ((realDate >> 5) & 0b1111)
		<< "/" << std::setw(2) << std::setfill('0') << (realDate & 0b11111);
		std::cout << "] defaulting to [" << (closestDate>> 9) << "/"
		<< std::setw(2) << std::setfill('0') << ((closestDate>> 5) & 0b1111)
		<< "/" << std::setw(2) << std::setfill('0') << (closestDate & 0b11111) << "] ";

		std::cout << value << " btc == "
		<< std::fixed << std::setprecision(2) << value * btcRate << " euros." << std::endl;
}

const char *BitcoinExchange::InvalidDatabaseException::what() const throw()
{
	return ("Database format is invalid\n");
}
const char *BitcoinExchange::InvalidFileException::what() const throw()
{
	return ("Invalid file\n");
}

int	BitcoinExchange::dateIsCorrect(int year, int month, int day)
{
	int leapYear = 0;
	if (year < 2004 || year > 2024)
		return (0);
	if (year % 400 == 0 || ((year % 4) == 0 && (year % 100) != 0))
		leapYear = 1;
	if (month < 1 || month > 12)
		return (0);
	if (day > 31 || day < 1)
		return (0);
	if (leapYear && month == 2 && day <= 29)
		return (1);
	if (!leapYear && month == 2 && day > 28)
		return (0);
	if (month % 2 == 0 && day > 30)
		return (0);
	return (1);
}

void	BitcoinExchange::compare(BitcoinExchange &toCompare)
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

void	BitcoinExchange::compareFile(std::string fileName)
{
	std::ifstream inputFile(fileName.c_str());
	if (inputFile)
	{
		std::string	buffer;

		getline(inputFile, buffer);
		if (buffer != "date | value")
			throw BitcoinExchange::InvalidDatabaseException();
		while (!inputFile.eof())
		{
			int year = 0, month = 0, day = 0;
			int date = 0;
			char div1 = 0, div2 = 0, div3 = 0;
			float value = 0;
			inputFile >> year >> div1 >> month >> div2 >> day >> div3 >> value;
			if (dateIsCorrect(year, month, day) && div1 == '-' && div2 == div1)
			{
				if (value < 0)
					std::cerr << "Error: not a positive number." << std::endl;
				if (value > 1000)
					std::cerr << "Error: value is too high." << std::endl;
				if (inputFile.fail())
				{
					inputFile.clear();
					std::string wesh;
					getline(inputFile, wesh);
					std::cerr << "Error: \"" << wesh << "\" is not an acceptable value." << std::endl;
				}
				else if (value > 0 && value <= 1000)
				{
					int approx = 0;
					date = (year << 9) | (month << 5) | day;
					std::map<int, float>::iterator found;
					found = this->_storage.lower_bound(date);
					if (found->first != date && found != this->_storage.begin())
					{
						approx = 1;
						found--;
					}
					if (approx)
						this->printApproxValue(date, found->first, value, found->second);
					else
						this->printExactValue(date, value, found->second);
				}
			}
			else if (inputFile.good())
				std::cout << "Error: invalid date." << std::endl;
		}
	}
	else
		throw BitcoinExchange::InvalidFileException();
}







