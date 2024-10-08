/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:39:11 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/29 21:56:02 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(const HumanA &ch): name(ch.name), weapon(ch.weapon)
{
	
}

HumanA::HumanA(std::string name, Weapon &weapon): name(name), weapon(weapon)
{
	std::cout << "HumanA " << name << " created with ";
	std::cout << weapon.getType() << std::endl;
}

HumanA::~HumanA(void)
{
	std::cout << "HumanA " << this->name << " destroyed" << std::endl;
}

void	HumanA::attack(void)
{
	std::cout << this->name << " attacks with his " << \
		this->weapon.getType() << std::endl;
}

void	HumanA::setWeapon(Weapon weapon)
{
	this->weapon = weapon;
}
