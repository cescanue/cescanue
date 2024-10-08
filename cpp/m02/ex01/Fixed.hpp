/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:17:40 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 16:11:25 by cescanue         ###   ########.fr       */
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
};
std::ostream	&operator<<(std::ostream &str, Fixed const &nbr);

#endif
