/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:56:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 10:07:18 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>

class Animal
{
protected:
    std::string type;

public:
    Animal( void );
    Animal( std::string type );
	virtual ~Animal( void );
    Animal( const Animal& s );
    Animal& operator=( const Animal& rhs );
    virtual void    makeSound( void ) const;
    std::string     getType( void ) const; 
};

#endif
