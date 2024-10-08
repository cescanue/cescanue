/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:36:38 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/29 21:05:19 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name );

int	main (void)
{
	int	count;
	Zombie *horde;

	count = 30;
	horde = zombieHorde(count, "Carlos");
	for (int n = 0; n < count ; n++)
		horde[n].announce();
	delete [] horde;
	return (0);
}
