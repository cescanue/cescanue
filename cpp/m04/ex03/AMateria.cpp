/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:34:06 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 20:57:11 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria( void ): type("")
{
    std::cout << "AMateria: materia is created *" << std::endl;
}

AMateria::AMateria( std::string const & t ): type(t)
{
    std::cout << "AMateria: " << this->type << " created" << std::endl;
}

AMateria::AMateria( AMateria const & s )
{
    *this = s;
}

AMateria::~AMateria( void )
{
    std::cout << "AMateria: " << this->type << " destroyed" << std::endl;
}

std::string const & AMateria::getType() const
{
    return this->type;
}

AMateria* AMateria::clone() const
{
    return (AMateria*)this;
}

void    AMateria::use( ICharacter& t )
{
    std::cout << "AMateria: " << this->type << " used on " << t.getName() << std::endl;
}
