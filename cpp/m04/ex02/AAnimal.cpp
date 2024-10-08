/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:31:02 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 10:39:13 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal( void ) : type( "AAnimal" ) {
    std::cout << this->type << ": constructor called" << std::endl;
}

AAnimal::AAnimal( std::string type ) : type( type )
{
    std::cout << "AAnimal: " << this->type << ": constructor called" << std::endl;
}

AAnimal::~AAnimal( void )
{
    std::cout << "AAnimal: destructor called" << std::endl;
}

AAnimal::AAnimal( const AAnimal& s )
{
    std::cout << "AAnimal: copy constructor called" << std::endl;
    *this = s;
}

AAnimal& AAnimal::operator=( const AAnimal& rhs )
{
    std::cout << "AAnimal: assignment operator called" << std::endl;
    if ( this != &rhs ) {
        this->type = rhs.type;
    }
    return *this;
}

void AAnimal::makeSound( void ) const
{
    std::cout << "AAnimal: makeSound called" << std::endl;
}

std::string    AAnimal::getType( void ) const
{
    return this->type;
}
