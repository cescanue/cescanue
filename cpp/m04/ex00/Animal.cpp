/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:57:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 09:59:09 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal( void ) : type( "Animal: " ) {
    std::cout << this->type << " constructor called" << std::endl;
}

Animal::Animal( std::string type ) : type( type )
{
    std::cout << "Animal: " << this->type << " constructor called" << std::endl;
}

Animal::~Animal( void )
{
    std::cout << "Animal: destructor called" << std::endl;
}

Animal::Animal( const Animal &s )
{
    std::cout << "Animal copy constructor called" << std::endl;
    *this = s;
}

Animal& Animal::operator=( const Animal& rhs )
{
    std::cout << "Animal: assignment operator called" << std::endl;
    if ( this != &rhs ) {
        this->type = rhs.type;
    }
    return *this;
}

void Animal::makeSound( void ) const
{
    std::cout << "Animal: makeSound called" << std::endl;
}

std::string    Animal::getType( void ) const
{
    return this->type;
}
