/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:17:40 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 16:29:24 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class	Fixed
{
	private:
		int					value;
		static const int	dot;
	public:
		Fixed(void);
		~Fixed(void);
		Fixed(Fixed const &cf);
		Fixed	&operator=(Fixed const &cf);
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		Fixed(const int value);
		Fixed(const float value);
		float	toFloat(void) const;
		int		toInt(void) const;
		bool    operator>( const Fixed &rhs ) const ;
		bool    operator<( const Fixed &rhs ) const ;
		bool    operator>=( const Fixed &rhs ) const ;
		bool    operator<=( const Fixed &rhs ) const ;
		bool    operator==( const Fixed &rhs ) const ;
		bool    operator!=( const Fixed &rhs ) const ;
		Fixed   operator+( const Fixed &rhs ) const ;
		Fixed   operator-( const Fixed &rhs ) const ;
		Fixed   operator*( const Fixed &rhs ) const ;
		Fixed   operator/( const Fixed &rhs ) const ;
		Fixed	&operator++( void );
		Fixed   operator++( int );
		Fixed	&operator--( void );
		Fixed   operator--( int );
		static Fixed& min( Fixed &a, Fixed &b );
		static const Fixed& min( const Fixed &a, const Fixed &b );
		static Fixed& max( Fixed &a, Fixed &b );
		static const Fixed& max( const Fixed &a, const Fixed &b );
};

std::ostream	&operator<<(std::ostream &str, Fixed const &nbr);

#endif
