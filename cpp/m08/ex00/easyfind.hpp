/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:03:17 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/15 16:41:38 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>

template <typename T>
typename T::iterator	easyfind(T &container, int n)
{
	if ( std::find( container.begin(), container.end(), n ) != container.end() )
		return (std::find( container.begin(), container.end(), n));
	else
		throw std::runtime_error("Value not found");
}

#endif

