/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:51:26 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/10 12:23:16 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int main()
{
	Array<int> intArray(5);
	for (unsigned int i = 0; i < intArray.size(); ++i)
		intArray[i] = i;
	std::cout << "intArray:";
	for (unsigned int i = 0; i < intArray.size(); ++i)
		std::cout << " " << intArray[i];
	std::cout << std::endl;

	Array<int> intArrayCPY(intArray);
	std::cout << "intArrayCPY:";
	for (unsigned int i = 0; i < intArrayCPY.size(); ++i)
		std::cout << " " << intArrayCPY[i];
	std::cout << std::endl;

	Array<int> intArrayCPYOprtr;
	intArrayCPYOprtr = intArray;
	std::cout << "intArrayCPYOperator:";
	for (unsigned int i = 0; i < intArrayCPYOprtr.size(); ++i)
		std::cout << " " << intArrayCPYOprtr[i];
	std::cout << std::endl;
	return 0;
}

