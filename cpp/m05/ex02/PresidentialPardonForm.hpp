/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:29:18 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/07 21:40:25 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

class Bureaucrat;

class PresidentialPardonForm: public Form
{
	private:
		std::string	_target;
	public:
		PresidentialPardonForm(void);
		PresidentialPardonForm(std::string const &target);
		PresidentialPardonForm(PresidentialPardonForm const &copy);
		~PresidentialPardonForm(void);
		PresidentialPardonForm const	&operator=(PresidentialPardonForm const &copy);
		void	beExecuted(Bureaucrat const &bureaucrat) const;
};

std::ostream	&operator<<(std::ostream &str, PresidentialPardonForm const &form);

#endif
