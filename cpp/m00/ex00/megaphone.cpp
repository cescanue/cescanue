/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:33:04 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/25 21:17:17 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int argc, char **argv)
{
	int	count;
	if (argc < 2)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		count = 1;
		while (argv[count])
		{
			while (*argv[count])
			{
				std::cout << (char) std::toupper(*argv[count]);
				(argv[count])++;
			}
			count++;
		}
	}
	std::cout << std::endl;
	return (0);
}
