/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:33:29 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 09:33:40 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap( std::string name ) : ClapTrap( name ), FragTrap( name ), ScavTrap( name )
{
    this->name = name;
    this->ClapTrap::name = name + "_clap_name";
    
    FragTrap::hitPoints = 100;
    ScavTrap::energyPoints = 50;
    FragTrap::attackDamage = 30;
    std::cout << "DiamondTrap: " << this->name << " constructed." << std::endl;
}

DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap: " << this->name << " is dead." << std::endl;
}

void    DiamondTrap::whoAmI( void ) {
    std::cout << "I am a DiamondTrap named " << this->name << ", ClapTrap name: " << ClapTrap::name << std::endl;
}
