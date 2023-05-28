#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &source)
{
	*this = source;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
	(void)rhs;
	return (*this);
}

PmergeMe::PmergeMe(int argc, char **argv)
{
	if (CheckArgs(argc - 1, argv + 1))
		throw PmergeMe::WrongValueException();
	for (int i = 0; i < argc; i++)
	{
		this->_listStorage.push_back(atoi(argv[i]));
	}
}

int PmergeMe::CheckArgs(int argc, char **argv)
{
	gettimeofday(&(this->_start), NULL);
	for (int i = 0; i < argc; i++)
	{
		for (unsigned int j = 0; j < strlen(argv[i]); j++)
		{
			if (!isdigit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}

const char *PmergeMe::WrongValueException::what() const throw()
{
	return ("Wrong input.");
}

double PmergeMe::getTimer() const
{
	return ((this->_timer.tv_sec * 1000) + (this->_timer.tv_usec / 1000));
}

void	PmergeMe::updateTimer()
{
	gettimeofday(&(this->_timer), NULL);
	this->_timer.tv_sec -= this->_start.tv_sec;
	this->_timer.tv_usec -= this->_start.tv_usec;
}
