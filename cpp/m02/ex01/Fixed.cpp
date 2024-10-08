/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:19:57 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 16:11:44 by cescanue         ###   ########.fr       */
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
	return (this->value);
}

void	Fixed::setRawBits(const int raw)
{
	this->value = raw;
}

Fixed::Fixed(const int value): value( value << dot)
{  
	std::cout << "Fixed: object created with int constructor" << std::endl; 
} 

Fixed::Fixed(const float value): value(std::roundf( value * ( 1 << dot)))
{  
	std::cout << "Fixed: object created with float constructor" << std::endl; 
} 

float	Fixed::toFloat(void) const
{
	return static_cast<float>( this->getRawBits() ) / ( 1 << dot );
}

int	Fixed::toInt(void) const
{
	return (value >> dot);
}

std::ostream	&operator<<(std::ostream &str, Fixed const &nbr)
{
	return (str << nbr.toFloat());
}
