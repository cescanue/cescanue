/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:09:52 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 10:10:20 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat( void ) : WrongAnimal("WrongCat")
{
    std::cout << this->type << ": constructor called" << std::endl;
}

WrongCat::~WrongCat( void )
{
    std::cout << this->type << ": destructor called" << std::endl;
}

void    WrongCat::makeSound( void ) const
{
    std::cout << "Miauuuuuuu..." << std::endl;
}
