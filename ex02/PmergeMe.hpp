#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <exception>
# include <list>
# include <vector>
# include <cstring>
# include <cstdlib>
# include <sys/time.h>

# define VECTOR_TIMER 0
# define LIST_TIMER 1

class PmergeMe
{
	public:
		~PmergeMe();
		PmergeMe(const PmergeMe &source);
		PmergeMe &operator=(const PmergeMe &rhs);
		PmergeMe(int argc, char **argv);

		int CheckArgs(int argc, char **argv);


		/* timer methods */
		void	updateTimer();
		double	getTimer() const;
		void	printTimer() const;

		/* exceptions */
		class WrongValueException : public std::exception
		{
			const char *what() const throw();
		};
	private:
		PmergeMe();
	protected:
		std::list<int> _listStorage;
		std::vector<int> _vectorStorage;

		struct timeval _start;
		struct timeval _timer;
};

#endif
