/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:03:25 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 10:35:11 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog( void ) : AAnimal( "Dog" )
{
    std::cout << this->type << ": constructor called" << std::endl;
}

Dog::~Dog( void )
{
    std::cout << this->type << ": destructor called" << std::endl;
}

void    Dog::makeSound( void ) const
{
    std::cout << "Guauuuuu!" << std::endl;
}
