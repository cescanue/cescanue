/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:04:54 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/08 11:30:42 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define BTCDB "data.csv"

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./btc <filename>" << std::endl;
		return (1);
	}
	try
	{
		BitcoinExchange btc(BTCDB, argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

