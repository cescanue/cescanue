/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:53:38 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 20:54:08 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice")
{
}

Ice::Ice( Ice const & src ) : AMateria("ice")
{
    *this = src;
}

Ice&   Ice::operator=( const Ice& rhs ) {
    if (this != &rhs)
    {
        this->type = rhs.type;
    }
    return *this;
}

Ice::~Ice()
{
}

AMateria* Ice::clone() const
{
    return (new Ice(*this));
}

void    Ice::use( ICharacter& target )
{
    std::cout << "I shoots an ice bolt at " << target.getName() << std::endl;
}
