/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:21:46 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 21:29:16 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap( std::string name ) : ClapTrap(name)
{
    this->hitPoints = 100;
    this->energyPoints = 100;
    this->attackDamage = 30;

    std::cout << "FragTrap: " << this->name << " Vitamin assembly." << std::endl;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap: " << this->name << " no more vitamins." << std::endl;
}

void    FragTrap::highFive( void ) {
    if ( this->energyPoints <= 0 ) {
        std::cout << "FragTrap:" << this->name << " is out of energy." << std::endl;
        return;
    }
    std::cout << "FragTrap: " << this->name << " high fives everybody." << std::endl;
    this->energyPoints -= 1;
}
