/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:31:45 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/10 12:23:45 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template <typename T>
void	swap(T &a, T &b)
{
	T	tmp;

	tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
T		min(T a, T b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

template <typename T>
T		max(T a, T b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

#endif

