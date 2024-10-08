/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:01:16 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 10:21:14 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat( void ) : Animal("Cat")
{
    std::cout << this->type << ": constructor called" << std::endl;
}

Cat::~Cat( void )
{
    std::cout << this->type << ": destructor called" << std::endl;
}

void    Cat::makeSound( void ) const
{
    std::cout << "Miauuuuuuu!!" << std::endl;
}
