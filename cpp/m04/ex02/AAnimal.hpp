/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:30:08 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 10:34:07 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
# define AANIMAL_HPP

#include <iostream>
#include "Brain.hpp"

class AAnimal
{
protected:
    std::string type;

public:
    AAnimal( void );
    AAnimal( std::string type );
    virtual ~AAnimal( void );
    AAnimal( const AAnimal& src );
    AAnimal& operator=( const AAnimal& rhs );
    virtual void    makeSound( void ) const = 0;
    std::string     getType( void ) const; 
};

#endif
