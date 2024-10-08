/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:13:32 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/21 11:32:16 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

uintptr_t	Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data*		Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*>(raw));
}

Serializer::Serializer(void)
{
	return;
}

Serializer::~Serializer(void)
{
	return;
}

Serializer::Serializer(Serializer const &src)
{
	*this = src;
	return;
}

Serializer	&Serializer::operator=(Serializer const &rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}
