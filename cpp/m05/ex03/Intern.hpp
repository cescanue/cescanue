/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:21:41 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/08 21:22:35 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Form;

class Intern
{
	public:
		Intern(void);
		Intern(Intern const &copy);
		~Intern(void);
		Intern const	&operator=(Intern const &copy);
		Form	*makeForm(std::string const &type, std::string const &target);
};

#endif
