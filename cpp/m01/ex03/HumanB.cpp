/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:41:04 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 14:45:59 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(): weapon(NULL)
{

}

HumanB::HumanB(const HumanB &ch): name(ch.name), weapon(ch.weapon)
{
	
}

HumanB::HumanB(std::string name): weapon(NULL)
{
	this->name = name;
	std::cout << "HumanB " << name << " created with no weapon" << std::endl;
}

HumanB::~HumanB(void)
{
	std::cout << "HumanB " << this->name << " destroyed" << std::endl;
}

void	HumanB::attack(void)
{
	
	std::cout << this->name << " attacks with his " << \
		this->weapon->getType() << std::endl;
}

void	HumanB::setWeapon(Weapon &weapon)
{
	this->weapon = &weapon;
}
