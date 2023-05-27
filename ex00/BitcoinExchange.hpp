#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <exception>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>

class BitcoinExchange
{
	public:
		~BitcoinExchange();
		BitcoinExchange(std::string fileName);

		void	compareFile(std::string fileName);
		void	compare(BitcoinExchange &toCompare);

		void	printExactValue(int date, float value, float btcRate);
		void	printApproxValue(int realDate, int closestDate, float value, float btcRate);
		/* Exceptions */
		class InvalidDatabaseException : public std::exception
		{
			public:
				const char *what() const throw();
		};
		class InvalidFileException : public std::exception
		{
			public:
				const char *what() const throw();
		};
		private:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &source);
		BitcoinExchange &operator=(const BitcoinExchange &rhs);

		int	dateIsCorrect(int year, int month, int day);
	protected:
		std::map<int, float> _storage;
};

#endif
