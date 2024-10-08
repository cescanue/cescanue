/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:20:50 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/21 11:27:45 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data(void)
{
	return;
}

Data::Data(std::string name) : _name(name)
{
	return;
}

Data::Data(Data &t)
{
	*this = t;
	return;
}

Data::~Data(void)
{
	return;
}	

Data & Data::operator=(const Data &t)
{
	this->_name = t._name;
	return (*this);
}

std::string	Data::getName() const
{
	return (this->_name);
}

void	Data::setName(std::string name)
{
	this->_name = name;
}

std::ostream & operator<<(std::ostream & o, Data const & rhs)
{
	o << rhs.getName();
	return (o);
}

