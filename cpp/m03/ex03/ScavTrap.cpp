/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:10:11 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 21:18:14 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap( std::string name ) : ClapTrap(name)
{
    this->hitPoints = 100;
    this->energyPoints = 50;
    this->attackDamage = 20;

    std::cout << "ScavTrap: " << this->name << " assembled." << std::endl;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap: " << this->name << " disassembled." << std::endl;
}

void    ScavTrap::attack( std::string const& target ) {
    if ( this->energyPoints <= 0 ) {
        std::cout << "ScavTrap: " << this->name << " is out of energy." << std::endl;
        return;
    }
    std::cout << "ScavTrap: " << this->name << " attacks " << target << " at range, causing " << this->attackDamage << " points of damage !" << std::endl;
    this->energyPoints -= 1;
}

void    ScavTrap::guardGate() {
    std::cout << "ScavTrap: " << this->name << " is now in Gate keeper mode." << std::endl;
}
