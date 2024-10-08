/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:17:40 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 15:23:51 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

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
};

#endif
