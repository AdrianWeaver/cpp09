#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(char* phrase)
{
	for (unsigned int i = 0; i < strlen(phrase); i++)
	{
		if (isdigit(phrase[i]))
		{
			this->_storage.push_front(phrase[i] - '0');
			continue;
		}
		else if (phrase[i] == '+' || phrase[i] == '-'
				|| phrase[i] == '/'|| phrase[i] == '*')
		{
			int tmp = this->_storage.front();
			this->_storage.pop_front();
			if (phrase[i] == '+')
				this->_storage.front() += (tmp);
			if (phrase[i] == '-')
				this->_storage.front() -= (tmp);
			if (phrase[i] == '/')
			{
				if (tmp == 0)
					throw RPN::DivideByZeroException();
				else
					this->_storage.front() /= (tmp);
			}
			if (phrase[i] == '*')
			{
				this->_storage.front() *= (tmp);
			}
		}
		else if (!isspace(phrase[i]))
			throw RPN::WrongInputException();
	}
}

RPN::RPN(const RPN &source)
{
	*this = source;
}

RPN &RPN::operator=(const RPN &rhs)
{
	this->_storage = rhs._storage;
	return (*this);
}

int	RPN::getTopValue()
{
	return (this->_storage.front());
}

const char*RPN::WrongInputException::what() const throw()
{
	return ("Wrong input.");
}

const char*RPN::DivideByZeroException::what() const throw()
{
	return ("Trying to divide by zero.");
}
