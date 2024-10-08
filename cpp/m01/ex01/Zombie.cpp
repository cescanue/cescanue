/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:01:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/29 21:00:41 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void Zombie::announce( void )
{
	std::cout << this->zname << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
Zombie::Zombie()
{

}

Zombie::Zombie(std::string name)
{
	this->zname = name;
}

Zombie::Zombie(const Zombie &cz)
{
	this->zname = cz.zname;
}

Zombie::~Zombie()
{
	std::cout << this->zname << ": Zombie destroyed" << std::endl;
}

void	Zombie::setName(std::string name)
{
	this->zname = name;
}

