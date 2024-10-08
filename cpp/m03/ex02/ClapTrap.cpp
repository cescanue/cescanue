/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:59:15 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 21:06:39 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap( std::string name ) : name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap: " << name << " is born!" << std::endl;
}

ClapTrap::~ClapTrap(void)
{
    std::cout << "ClapTrap: destructor called" << std::endl;
    return;
}

ClapTrap::ClapTrap(const ClapTrap &rhs)
{
    *this = rhs;
    std::cout << "ClapTrap: copy constructor called" << std::endl;
    return;
}

ClapTrap&   ClapTrap::operator=( const ClapTrap& rhs ) {
    this->name = rhs.name;
    this->hitPoints = rhs.hitPoints;
    this->energyPoints = rhs.energyPoints;
    this->attackDamage = rhs.attackDamage;
    return *this;
}

void    ClapTrap::attack( std::string const& target )
{
    if (energyPoints <= 0)
    {
        std::cout << "ClapTrap: " << name << " is out of energy!" << std::endl;
        return;
    }
    std::cout << "ClapTrap: " << name << " attacks " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
    energyPoints -= 1;
}

void    ClapTrap::takeDamage( unsigned int amount )
{
    if (hitPoints <= amount)
    {
        std::cout << "ClapTrap: " << name << " is dead!" << std::endl;
        return;
    }
    std::cout << "ClapTrap: " << name << " takes " << amount << " damage!" << std::endl;
    hitPoints -= amount;
}

void    ClapTrap::beRepaired( unsigned int amount )
{
    if (energyPoints <= amount)
    {
        std::cout << "ClapTrap: " << name << " is out of energy!" << std::endl;
        return;
    }
    std::cout << "ClapTrap: " << name << " repairs itself for " << amount << " hit points!" << std::endl;
    energyPoints -= 1;
    hitPoints += amount;
}
