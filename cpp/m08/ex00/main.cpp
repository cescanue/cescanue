/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:05:19 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/15 21:26:21 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <vector>
#include <list>

int		main(void)
{
	std::vector<int>	v;
	std::list<int>		l;

	v.push_back(5);
	v.push_back(3);
	v.push_back(17);
	v.push_back(9);
	v.push_back(11);
	try {
		std::cout << *easyfind(v, 5) << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		std::cout << *easyfind(v, 4) << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	l.push_back(5);
	l.push_back(3);
	l.push_back(17);
	l.push_back(9);
	l.push_back(11);
	try {
		std::cout << *easyfind(l, 5) << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		std::cout << *easyfind(l, 4) << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	
	
	
	
	return (0);
}

