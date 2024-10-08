/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:16:59 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/07 21:18:47 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include "Form.hpp"

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

class Bureaucrat;

class ShrubberyCreationForm: public Form
{
	private:
		std::string	_target;
	public:
		ShrubberyCreationForm(void);
		ShrubberyCreationForm(std::string const &target);
		ShrubberyCreationForm(ShrubberyCreationForm const &copy);
		~ShrubberyCreationForm(void);
		ShrubberyCreationForm const	&operator=(ShrubberyCreationForm const &copy);
		void	beExecuted(Bureaucrat const &bureaucrat) const;
};

std::ostream	&operator<<(std::ostream &str, ShrubberyCreationForm const &form);

#endif
