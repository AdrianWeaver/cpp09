#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <iomanip>
# include <exception>
# include <deque>
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


		/* getters */
		int	getVectorStorageSize() const;

		/* timer methods */
		void	updateTimer();
		double	getTimer() const;
		void	printTimer() const;

		/* sorting methods */
		void	sort();
		void	fordJohnson(std::vector<int>& A, int p, int r);
		void	insertionSort(std::vector<int>& A, int p, int q);
		void	merge(std::vector<int>& A, int p, int q, int r);
		void	fordJohnson(std::deque<int>& A, int p, int r);
		void	insertionSort(std::deque<int>& A, int p, int q);
		void	merge(std::deque<int>&, int start, int finish, int recursion);

		bool	isVectorStorageSorted();
		void	printVector(std::vector<int> &container);
		void	printVectorStorage();

		/* exceptions */
		class WrongValueException : public std::exception
		{
			const char *what() const throw();
		};
	private:
		PmergeMe();
	protected:
		std::vector<int> _vectorStorage;
		std::deque<int> _dequeStorage;

		struct timeval _start;
		struct timeval _timer;
};

#endif
