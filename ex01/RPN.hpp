#ifndef RPN_HPP
# define RPN_HPP

# include <list>
# include <cctype>
# include <exception>
# include <iostream>
# include <cstring>


class RPN
{
	public:
		~RPN();
		RPN(char* argv);
		RPN(const RPN &source);
		RPN &operator=(const RPN &rhs);

		int	getTopValue();
		/* exceptions */
		class WrongInputException : public std::exception
		{
			const char *what() const throw();
		};

		class DivideByZeroException : public std::exception
		{
			const char *what() const throw();
		};
		int	compute();
	private:
		RPN();
	protected:
		std::list<int> _storage;
};

#endif
