/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:01:38 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/20 13:12:13 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./convert [string]" << std::endl;
		return (0);
	}
	try {
		ScalarConverter::Convert(argv[1]);
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return (0);
	}
	return (0);
}
