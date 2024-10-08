/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:06:05 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 10:08:12 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal( void ) : type( "WrongAnimal" ) {
    std::cout << this->type << ": constructor called" << std::endl;
}

WrongAnimal::WrongAnimal( std::string type ) : type( type )
{
    std::cout << "WrongAnimal: " << this->type << " constructor called" << std::endl;
}

WrongAnimal::~WrongAnimal( void )
{
    std::cout << "WrongAnimal: destructor called" << std::endl;
}

WrongAnimal::WrongAnimal( const WrongAnimal& s )
{
    std::cout << "WrongAnimal: copy constructor called" << std::endl;
    *this = s;
}

WrongAnimal& WrongAnimal::operator=( const WrongAnimal& rhs )
{
    std::cout << "WrongAnimal: assignment operator called" << std::endl;
    if ( this != &rhs ) {
        this->type = rhs.type;
    }
    return *this;
}

void WrongAnimal::makeSound( void ) const
{
    std::cout << "WrongAnimal: makeSound called" << std::endl;
}

std::string    WrongAnimal::getType( void ) const
{
    return this->type;
}
