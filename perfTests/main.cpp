#include <iostream>
#include <algorithm>
#include <functional>
#include <random>
#include <chrono>
#include <vector>
#include <list>
#include <iterator>

struct TrueType {
	static constexpr bool value = true;
};


void sort(std::vector<int>::iterator, std::vector<int>::iterator, int);
void sort(std::vector<int>&, int);
bool areEqual(std::vector<int>, std::vector<int>);
std::function<int()> createUniformDist(int);
void createRandomVector(std::vector<int>&, int, int);
unsigned long myPow(long, long);
int fastPower(int, int);

std::ostream& operator<<(std::ostream&, std::vector<int>);

void sortTest();
void powTest();
void isSortedTest();

template <class iter> 
struct is_bidirectional_iter : std::is_same< typename std::iterator_traits<iter>::iterator_category, std::bidirectional_iterator_tag> {};

template <class iter, class T = void>
struct enable_if_bidirectional : std::enable_if<is_bidirectional_iter<iter>::value, T> {};

template <class Iter>
typename std::enable_if<std::is_same< typename std::iterator_traits<Iter>::iterator_category, std::random_access_iterator_tag>::value>::type 
print(Iter start, Iter end)
{
	auto it = start;
	while (it != end)
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "Random access iterator version" << std::endl;
}

template <class Iter>
typename enable_if_bidirectional<Iter>::type
print(Iter start, Iter end)
{
	auto it = start;
	while (it != end)
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "Bidirectional iterator version" << std::endl;
}

template <class T>
void identify(T& cont)
{
	std::cout << "Unkown" << std::endl;
}

template <>
void identify(std::vector<int>& cont)
{
	std::cout << "std::vector<int>" << std::endl;
}

template <>
void identify(std::list<int>& cont)
{
	std::cout << "std::list<int>" << std::endl;
}


template <>
void identify(std::list<bool>& cont)
{
	std::cout << "std::list<bool>" << std::endl;
}


int main()
{
	//std::cout << "Hello World!" << std::endl;
	//myPow(3, 20);
	std::vector<int> v = {1, 2, 3, 4, 5};
	std::list<int> l = { 1, 2, 3, 4, 5 };;
	std::list<bool> lb;
	identify(v);
	identify(l);
	identify(lb);
	print(v.begin(), v.end());
	print(l .begin(), l.end());
	//powTest();
	getchar();
}

void isSortedTest()
{
	std::vector<int> vec = { 1, 2, 3, 4, 4 };
	auto compare = [](int a, int b) -> bool
	{
		return a == b;
	};

	std::vector<int>::iterator it = std::is_sorted_until(vec.begin(), vec.end(), compare);
	if (it != vec.end())
	{
		std::cout << *it << std::endl;
		std::cout << "Vector not sorted." << std::endl;
	}

}

void powTest()
{
	const int range = 50;
	const int size = 100;

	std::vector<int> base, exp;
	createRandomVector(base, size, range);
	createRandomVector(exp, size, range);

	std::vector<int> resultsStd(size);
	std::vector<int> resultsMy(size);
	for (size_t index = 0; index < size; index++)
	{
		resultsStd[index] = std::pow(base[index], exp[index]);
		resultsMy[index] = myPow(base[index], exp[index]);
	}

	if (areEqual(resultsStd, resultsMy))
	{
		std::cout << "Both equal after." << std::endl;
	}
	else
	{
		auto temp = std::mismatch(resultsMy.begin(), resultsMy.end(), resultsStd.begin());
		std::cout << "Not equal after: " << *temp.first << " " << *temp.second  << std::endl;
		std::cout << "Base: " << base[std::distance(resultsMy.begin(), temp.first)] << std::endl;
		std::cout << "Exponent: " << exp[std::distance(resultsMy.begin(), temp.first)] << std::endl;
	}

	std::cout << resultsMy << std::endl;
	std::cout << resultsStd << std::endl;
}


unsigned long myPow(long base, long exp)
{
	std::cout << "true: " << std::pow(base, exp) << std::endl;
	unsigned long res = 1;
	while (exp)
	{
		res *= base;
		exp--;
	}
	std::cout << "Mine: " << res << std::endl;
	std::cout << std::numeric_limits<long>::max() << std::endl;
	return  res;
}

void sortTest()
{
	const int range = 1000;
	const int size = 1000000;
	std::function<int()> randomInt = createUniformDist(range);

	std::vector<int> random;
	random.reserve(size);

	std::chrono::time_point<std::chrono::high_resolution_clock> startP, middleP, endP;
	uint64_t duration;

	for (int i = 0; i < size; i++)
	{
		random.push_back(randomInt());
	}

	std::vector<int> copy(random);
	if (areEqual(random, copy))
	{
		std::cout << "Both equal before." << std::endl;
	}

	startP = std::chrono::high_resolution_clock::now();
	std::sort(random.begin(), random.end());

	middleP = std::chrono::high_resolution_clock::now();
	sort(copy, 1000);

	endP = std::chrono::high_resolution_clock::now();


	if (areEqual(random, copy))
	{
		std::cout << "Both equal after." << std::endl;
	}
	if (std::is_sorted(copy.begin(), copy.end()))
	{
		std::cout << "Sorted correctly." << std::endl;
	}
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(middleP - startP).count();
	std::cout << "Duration for std::sort in nanoseconds:" << duration << std::endl;

	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endP - middleP).count();
	std::cout << "Duration for range based sort in nanoseconds:" << duration << std::endl;

	getchar();
}

void sort(std::vector<int>::iterator begin, std::vector<int>::iterator end, int range)
{
	std::vector<int> hist(range);

}

void sort(std::vector<int>& unsorted, int range)
{
	std::vector<int> hist(range + 1);
	for (auto it : unsorted)
	{
		hist[it]++;
	}

	int number = 0;
	int index = 0;
	for (int it : hist)
	{
		for (int i = 0; i < it; i++)
		{
			unsorted[index++] = number;
		}
		number++;
	}
}

bool areEqual(std::vector<int> left, std::vector<int> right)
{
	if (left.size() != right.size())
		return false;

	for (size_t index = 0; index < left.size(); index++)
	{
		if (left[index] != right[index])
			return false;
	}

	return true;
}


std::function<int()> createUniformDist(int range)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, range);
	return std::bind(dis, gen);
}

void createRandomVector(std::vector<int>& vec, int size, int range)
{
	std::function<int()> randomInt = createUniformDist(range);
	for (int i = 0; i < size; i++)
	{
		vec.push_back(randomInt());
	}
}

std::ostream& operator<<(std::ostream& os, std::vector<int> rhs)
{
	for (auto x : rhs)
	{
		os << x << " ";
	}
	os << std::endl;
	return os;
}