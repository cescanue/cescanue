/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:50:19 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/10 12:22:58 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>

template <typename T>
class	Array
{
	public:
		Array(void) : _array(NULL), _length(0) {}
		Array(unsigned int n) : _array(new T[n]), _length(n) {}
		Array(Array const &src) : _array(NULL), _length(0) { *this = src; }
		~Array(void) { delete [] _array; }
		Array	&operator=(Array const &rhs)
		{
			if (this != &rhs)
			{
				delete [] _array;
				_length = rhs._length;
				_array = new T[_length];
				for (unsigned int i = 0; i < _length; i++)
					_array[i] = rhs._array[i];
			}
			return (*this);
		}
		T		&operator[](unsigned int n)
		{
			if (n >= _length)
				throw std::exception();
			return (_array[n]);
		}
		unsigned int	size(void) const { return (_length); }
	private:
		T				*_array;
		unsigned int	_length;
};

#endif

