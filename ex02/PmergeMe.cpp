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
	gettimeofday(&(this->_start), NULL);
	for (int i = 1; i < argc; i++)
		this->_vectorStorage.push_back(atoi(argv[i]));
	this->updateTimer();
	this->_timerStoreVector = this->getTimer();
	gettimeofday(&(this->_start), NULL);
	for (int i = 1; i < argc; i++)
		this->_dequeStorage.push_back(atoi(argv[i]));
	this->updateTimer();
	this->_timerStoreDeque = this->getTimer();
}

int PmergeMe::CheckArgs(int argc, char **argv)
{
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
	return ((this->_timer.tv_sec * 1000.0) + (this->_timer.tv_usec / 1000.0));
}

int		PmergeMe::getVectorStorageSize() const
{
	return (this->_vectorStorage.size());
}

void	PmergeMe::updateTimer()
{
	gettimeofday(&(this->_timer), NULL);
	this->_timer.tv_sec -= this->_start.tv_sec;
	this->_timer.tv_usec -= this->_start.tv_usec;
}

bool	PmergeMe::isVectorStorageSorted()
{
	for (std::vector<int>::iterator it = this->_vectorStorage.begin();
		it < this->_vectorStorage.end(); it++)
	{
		if (it + 1 == this->_vectorStorage.end())
			return (true);
		if (*it > *(it + 1))
			return (false);
	}
	return (true);
}

void	PmergeMe::printVector(std::vector<int> &container)
{
	for (std::vector<int>::iterator it = container.begin();
		it != container.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;

}

void	PmergeMe::printVectorStorage()
{
	printVector(this->_vectorStorage);
}


void PmergeMe::insertionSort(std::vector<int>& storage, int lowRange, int oddHandler)
{
	for (int i = lowRange; i < oddHandler; i++)
	{
		int tempVal = storage[i + 1];
		int j = i + 1;
		while (j > lowRange && storage[j - 1] > tempVal)
		{
			storage[j] = storage[j - 1];
			j--;
		}
		storage[j] = tempVal;
	}
}

void PmergeMe::merge(std::vector<int>& storage, int lowRange, int oddHandler, int highRange)
{
	int sizeOfFirstPart = oddHandler - lowRange + 1;
	int sizeOfSecondPart = highRange - oddHandler;
	std::vector<int> firstPart(storage.begin() + lowRange, storage.begin() + oddHandler + 1);
	std::vector<int> secondPart(storage.begin() + oddHandler + 1, storage.begin() + highRange + 1);
	int secondPartIndex = 0;
	int firstPartIndex = 0;
	for (int i = lowRange; i < highRange - lowRange + 1; i++)
	{
		if (secondPartIndex == sizeOfSecondPart)
		{
			storage[i] = firstPart[firstPartIndex];
			firstPartIndex++;
		}
		else if (firstPartIndex == sizeOfFirstPart)
		{
			storage[i] = secondPart[secondPartIndex];
			secondPartIndex++;
		}
		else if (secondPart[secondPartIndex] > firstPart[firstPartIndex])
		{
			storage[i] = firstPart[firstPartIndex];
			firstPartIndex++;
		}
		else
		{
			storage[i] = secondPart[secondPartIndex];
			secondPartIndex++;
		}
	}
}

void PmergeMe::fordJohnson(std::vector<int>& storage, int lowRange, int highRange) {
	if (highRange - lowRange > static_cast<int>((storage.size() / 2)))
	{
		int	oddHandler = (lowRange + highRange) / 2;

		fordJohnson(storage, lowRange, oddHandler);
		fordJohnson(storage, oddHandler + 1, highRange);
		merge(storage, lowRange, oddHandler, highRange);
	}
	else
		insertionSort(storage, lowRange, highRange);
}

void PmergeMe::insertionSort(std::deque<int>& storage, int lowRange, int oddHandler)
{
	for (int i = lowRange; i < oddHandler; i++)
	{
		int tempVal = storage[i + 1];
		int j = i + 1;
		while (j > lowRange && storage[j - 1] > tempVal)
		{
			storage[j] = storage[j - 1];
			j--;
		}
		storage[j] = tempVal;
	}
}

void PmergeMe::merge(std::deque<int>& storage, int lowRange, int oddHandler, int highRange)
{
	int sizeOfFirstPart = oddHandler - lowRange + 1;
	int sizeOfSecondPart = highRange - oddHandler;
	std::deque<int> firstPart(storage.begin() + lowRange, storage.begin() + oddHandler + 1);
	std::deque<int> secondPart(storage.begin() + oddHandler + 1, storage.begin() + highRange + 1);
	int secondPartIndex = 0;
	int firstPartIndex = 0;
	for (int i = lowRange; i < highRange - lowRange + 1; i++)
	{
		if (secondPartIndex == sizeOfSecondPart)
		{
			storage[i] = firstPart[firstPartIndex];
			firstPartIndex++;
		}
		else if (firstPartIndex == sizeOfFirstPart)
		{
			storage[i] = secondPart[secondPartIndex];
			secondPartIndex++;
		}
		else if (secondPart[secondPartIndex] > firstPart[firstPartIndex])
		{
			storage[i] = firstPart[firstPartIndex];
			firstPartIndex++;
		}
		else
		{
			storage[i] = secondPart[secondPartIndex];
			secondPartIndex++;
		}
	}
}

void PmergeMe::fordJohnson(std::deque<int>& storage, int lowRange, int highRange) {
	if (highRange - lowRange > static_cast<int>((storage.size() / 2)))
	{
		int	oddHandler = (lowRange + highRange) / 2;

		fordJohnson(storage, lowRange, oddHandler);
		fordJohnson(storage, oddHandler + 1, highRange);
		merge(storage, lowRange, oddHandler, highRange);
	}
	else
		insertionSort(storage, lowRange, highRange);
}

void	PmergeMe::sort()
{
	gettimeofday(&(this->_start), NULL);
	this->fordJohnson(this->_vectorStorage, 0, this->_vectorStorage.size() - 1);
	this->updateTimer();
	this->_timerSortVector = this->getTimer();
	gettimeofday(&(this->_start), NULL);
	this->fordJohnson(this->_dequeStorage, 0, this->_vectorStorage.size() - 1);
	this->updateTimer();
	this->_timerSortDeque = this->getTimer();
}

void	PmergeMe::printTimers() const
{
	std::cout << std::setprecision(4) << std::fixed;
	std::cout << "Time to process a range of " << this->_vectorStorage.size()
		<< " elements with std::vector<int> to store data: " << this->_timerStoreVector
		<< "ms." << std::endl;
	std::cout << "Time to process a range of " << this->_vectorStorage.size()
		<< " elements with std::deque<int> to store data: " << this->_timerStoreDeque
		<< "ms." << std::endl;
	std::cout << "Time to process a range of " << this->_vectorStorage.size()
		<< " elements with std::vector<int> to sort data: " << this->_timerSortVector
		<< "ms." << std::endl;
	std::cout << "Time to process a range of " << this->_vectorStorage.size()
		<< " elements with std::deque<int> to sort data: " << this->_timerSortDeque
		<< "ms." << std::endl;
}
