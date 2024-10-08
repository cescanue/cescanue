/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:26:30 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/18 21:25:17 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"



void PmergeMe::Jacobsthal(void)
{
	unsigned cj = 0;
	std::vector<unsigned int> j;
	std::vector<unsigned int>::iterator ite;
	
	this->_jacob.clear();
	j.push_back(0);
	j.push_back(1);
	for (unsigned int i = 2; cj < MAXJ; i++)
	{
		cj = j[i - 1] + (2 * j[i - 2]);
		j.push_back(cj);
	}
	ite  = j.begin() + 3;
	while (ite != j.end())
	{
		this->_jacob.push_back((*ite));
		if (*ite - *(ite - 1) > 1)
			for (unsigned int c = *ite - 1 ; c > *(ite - 1); c--)
				this->_jacob.push_back((c));
		ite++;
	}
}
template <typename T>
void PmergeMe::print(T v)
{
	typename T::iterator ite = v.begin();
	while (ite != v.end())
		std::cout << *ite++ << " ";
	std::cout << std::endl;
}

template <typename T>
T PmergeMe::sort(T v)
{	
	if (v.size() -1 < 1)
		return v;
	int s = -1;
	T main;
	T pend;
	if (v.size() % 2)
	{
		s = v.back();
		v.pop_back();
	}
	int mid = v.size() / 2;
	typename T::iterator itr = v.begin();
	for (int i = 0; mid > 1 && i < (int) mid; i++)
	{
		if (*itr < *(++itr))
		{
			std::iter_swap(itr, --itr);
			itr += 2;
		}
		else 
			itr++;
	}
	v = this->quicksort(v);
	while (!v.empty())
	{
		main.push_back(v.front());
		v.erase(v.begin());
		pend.push_back(v.front());
		v.erase(v.begin());
	}
	if (s != -1)
		pend.push_back(s);
	if (pend.front() < main.front())
	{
		main.insert(main.begin(), pend.front());
		pend.erase(pend.begin());
	}
	int posj = 0;
	int pos = MAXJ;
	for (int i = 0; i < (int) pend.size(); i++)
	{
		while ((pos = _jacob[posj++] - 2) > (int) pend.size() - 1);
		typename T::iterator ite = main.begin();
		ite = ite + binarySearch(main, pend[pos], 0, pos + i + 1);
		main.insert(ite, pend[pos]);
	}
	return main;
}

template <typename T>
int PmergeMe::binarySearch(T array, unsigned  target, int begin, int end)
{
	int mid;

	if (end > (int) array.size() - 1)
		end = (int) array.size() - 1 ;
	if (begin < 0)
		begin = 0;
	while (begin <= end)
	{
		mid = begin + (end - begin) / 2;
		if (target == array[mid])
			return (mid);
		if (target > array[mid])
			begin = mid + 1;
		else
			end = mid - 1;
	}
	if (target > array[mid])
		return (mid + 1);
	else
		return (mid);
}

template <typename T>
T PmergeMe::quicksort(T co)
{
	if (co.size() <= 2)
		return co;	
	int mid = co.size() / 4;
	T left;
	T right;
	T result;

	for (int i = 0; i < mid; i++)
	{
		left.push_back(co.front());
		co.erase(co.begin());
		left.push_back(co.front());
		co.erase(co.begin());
	}
	right = co;
	left = quicksort(left);
	right = quicksort(right);
	while (!left.empty() && !right.empty())
	{
		if (left.front() < right.front())
		{
			result.push_back(left.front());
			left.erase(left.begin());
			result.push_back(left.front());
			left.erase(left.begin());
		}
		else
		{
			result.push_back(right.front());
			right.erase(right.begin());
			result.push_back(right.front());
			right.erase(right.begin());
		}
	}
	while (!left.empty())
	{
		result.push_back(left.front());
		left.erase(left.begin());
		result.push_back(left.front());
		left.erase(left.begin());
	}
	while (!right.empty())
	{
		result.push_back(right.front());
		right.erase(right.begin());
		result.push_back(right.front());
		right.erase(right.begin());
	}
	return result;
}

PmergeMe::PmergeMe(std::vector<unsigned int> numbers)
{
	struct timeval iniciov, finv, iniciod, find, iniciolst, finlst;
	std::vector<unsigned int> v;
	std::deque<unsigned int> d(numbers.begin(), numbers.end());
	MyList<unsigned int> lst;
	std::copy( numbers.begin(), numbers.end(), std::back_inserter( lst ) );
	this->Jacobsthal();
	std::cout << "Before: ";
	this->print(numbers);
	gettimeofday(&iniciov, NULL);
	v = this->sort(numbers);
	gettimeofday(&finv, NULL);
	gettimeofday(&iniciod, NULL);
	d = this->sort(d);
	gettimeofday(&find, NULL);
	gettimeofday(&iniciolst, NULL);
	lst = this->sort(lst);
	gettimeofday(&finlst, NULL);
	std::cout << "After : ";
	this->print(v);
	long duracionv = (finv.tv_sec - iniciov.tv_sec) * 1000000L + finv.tv_usec - iniciov.tv_usec;
	long duraciond = (find.tv_sec - iniciod.tv_sec) * 1000000L + find.tv_usec - iniciod.tv_usec;
	long duracionlst = (finlst.tv_sec - iniciolst.tv_sec) * 1000000L + finlst.tv_usec - iniciolst.tv_usec;
	std::cout << "Time to process a range of " << numbers.size()  << " elements with std::vector : " << duracionv << " ms" << std::endl;
	std::cout << "Time to process a range of " << numbers.size()  << " elements with std::deque  : " << duraciond << " ms" << std::endl;
	std::cout << "Time to process a range of " << numbers.size()  << " elements with std::list   : " << duracionlst << " ms" << std::endl;
	return ;
}

PmergeMe::PmergeMe(void)
{
	return ;
}

PmergeMe::PmergeMe(PmergeMe const &src)
{
	*this = src;
	return ;
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

PmergeMe	&PmergeMe::operator=(PmergeMe const &rhs)
{
	if (this != &rhs)
	{
		
	}
	return (*this);
}

