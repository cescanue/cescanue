/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:40:47 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/10 12:23:32 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

#include <iostream>

template <typename T>
void	print(T const &x)
{
	std::cout << x << std::endl;
}

int main(void)
{
	int		array1[5] = {1, 2, 3, 4, 5};
	char	array2[5] = {'a', 'b', 'c', 'd', 'e'};

	iter(array1, 5, print);
	iter(array2, 5, print);
	return (0);
}
