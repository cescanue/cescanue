/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:19:57 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 15:28:59 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::dot = 8;

Fixed::Fixed(void): value(0)
{
	std::cout << "Fixed: Default constructor called" << std::endl; 
}

Fixed::~Fixed(void)
{
	std::cout << "Fixed: destroyed" << std::endl; 
}

Fixed::Fixed(Fixed const & cf)
{
	std::cout << "Fixed: Copy construtor called" << std::endl;
	*this = cf;
}

Fixed	&Fixed::operator=(const Fixed &cf)
{
	std::cout << "Fixed: Assignment operator called" << std::endl;
	this->value = cf.getRawBits();
	return (*this);
}

int	Fixed::getRawBits(void) const
{
	std::cout << "Fixed: getRawBits member function called" << std::endl;
	return (this->value);
}

void	Fixed::setRawBits(const int raw)
{
	this->value = raw;
}
