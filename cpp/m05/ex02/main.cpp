/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:57:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/07 21:51:40 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
	ShrubberyCreationForm shrubbery("Casa Bonita");
	RobotomyRequestForm robotomy("Carlos");
	PresidentialPardonForm pardon("Pedro Sanchez");
	Bureaucrat Carlos("Carlos", 150);
	Bureaucrat Monica("Monica", 120);
	Bureaucrat Alba("Alba", 3);
	try
	{
		std::cout << Carlos << std::endl;
		std::cout << shrubbery << std::endl;
		std::cout << robotomy << std::endl;
		std::cout << pardon << std::endl;
		Carlos.executeForm(shrubbery);
		Carlos.executeForm(robotomy);
		Carlos.executeForm(pardon);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << Monica << std::endl;
		std::cout << Alba << std::endl;
		std::cout << shrubbery << std::endl;
		std::cout << robotomy << std::endl;
		std::cout << pardon << std::endl;
		shrubbery.beSigned(Alba);
		Monica.executeForm(shrubbery);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		robotomy.beSigned(Monica);
		pardon.beSigned(Monica);
		std::cout << shrubbery << std::endl;
		std::cout << robotomy << std::endl;
		std::cout << pardon << std::endl;
		
		std::cout << "\n --------------------- \n\n";
		Monica.executeForm(shrubbery);
		std::cout << "\n --------------------- \n\n";
		Monica.executeForm(robotomy);
		std::cout << "\n --------------------- \n\n";
		Monica.executeForm(pardon);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
