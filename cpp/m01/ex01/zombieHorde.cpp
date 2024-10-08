/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:52:33 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/29 20:59:46 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	Zombie	*hZombie;

	hZombie = new Zombie[N];
	for (int n = 0; n < N ;n++)
		hZombie[n].setName(name);
	return (hZombie);
}
