/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:22:00 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/18 21:29:43 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <list>
# include <vector>
# include <algorithm>
# include <deque>
# include <cstdlib>
# include <iomanip>
# include <sys/time.h>
# include "MyList.hpp"

# define MAXJ 87382

class PmergeMe
{
	private:
		std::vector<unsigned int> _jacob;
		PmergeMe(void);
		void Jacobsthal(void);
		template <typename T>
		void print(T);
		template <typename T>
		T sort(T);
		template <typename T>
		T quicksort(T);
		template <typename T>
		int binarySearch(T array, unsigned int target, int begin, int end);
	public:
		PmergeMe(std::vector<unsigned int> numbers);
		PmergeMe(PmergeMe const &src);
		~PmergeMe(void);
		PmergeMe	&operator=(PmergeMe const &rhs);
};

#endif
