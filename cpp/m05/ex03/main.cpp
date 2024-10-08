/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:57:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/08 21:47:47 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Intern.hpp"
#include "Bureaucrat.hpp"

int main(void)
{
	Intern		Carlos;
	Form		*form;
	Bureaucrat	Monica("Monica", 50);
	try
	{
		form = Carlos.makeForm("robotomy request", "Fina");
		delete form;
		form = Carlos.makeForm("shrubbery creation", "Pep");
		delete form;
		form = Carlos.makeForm("presidential pardon", "Pedro");
		delete form;
		form = Carlos.makeForm("random request", "Nuria");
		delete form;
	}
	catch (std::exception &e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}
	std::cout << "------------------------------------" << std::endl;
	form = Carlos.makeForm("shrubbery creation", "Julian");
	form->beSigned(Monica);
	Monica.executeForm(*form);
	delete form;
	std::cout << "------------------------------------" << std::endl;
	form = Carlos.makeForm("presidential pardon", "Lina");
	Monica.signForm(*form);
	Monica.executeForm(*form);
	delete form;
	return (0);
}
