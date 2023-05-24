#ifndef DATABASE_HPP
# define DATABASE_HPP

#include <string>
#include <map>
#include <exception>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>

class Database
{
	public:
		~Database();
		Database(std::string fileName);

		void	compareFile(std::string fileName);
		void	compare(Database &toCompare);
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
		Database();
		Database(const Database &source);
		Database &operator=(const Database &rhs);

		int	dateIsCorrect(int year, int month, int day);
	protected:
		std::map<int, float> _storage;
};

#endif
