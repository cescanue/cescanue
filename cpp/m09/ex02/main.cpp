/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:21:52 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/17 12:52:48 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		std::vector<unsigned int> numbers;
		for (int i = 1; i < argc; ++i)
		{
			if (argv[i][0] < '0' || argv[i][0] > '9')
			{
				std::cout << "Error: bad arguments" << std::endl;
				return (1);
			}
			numbers.push_back(atoi(argv[i]));
		}
		PmergeMe pmerge(numbers);
	}
	else
		std::cout << "PmergeMe: Use me with some numbers as arguments" << std::endl;
	return (0);
}

