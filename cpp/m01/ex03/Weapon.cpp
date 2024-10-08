/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:32:07 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/29 21:48:38 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type)
{
	this->setType(type);
}

Weapon::Weapon()
{

}

Weapon::Weapon(const Weapon &cw): type(cw.type)
{

}

Weapon::~Weapon()
{

}

void	Weapon::setType(std::string type)
{
	this->type = type;	
}

const std::string& Weapon::getType(void)
{
	return (this->type);
}
