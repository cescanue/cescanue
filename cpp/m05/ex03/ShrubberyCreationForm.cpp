/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:19:04 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/08 21:38:00 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include "Form.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void): Form::Form("ShrubberyCreationForm", 145, 137), _target("null") {}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target): Form::Form("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &copy): Form::Form(copy), _target(copy._target) {}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {}

ShrubberyCreationForm const	&ShrubberyCreationForm::operator=(const ShrubberyCreationForm &copy)
{
	Form::operator=(copy);
	this->_target = copy._target;
	return (*this);
}

void	ShrubberyCreationForm::beExecuted(const Bureaucrat &bureaucrat) const
{
	std::ofstream	fout;
	
	fout.open((this->_target + "_shrubbery").c_str());
	if (fout.fail())
	{
		std::cout << "Could not open output file" << std::endl;
		return ;
	}
	fout << "       _-_\n    /~~   ~~\\\n /~~         ~~\\\n{               }\n \\  _-     -_  /\n   ~  \\\\ //  ~\n_- -   | | _- _\n  _ -  | |   -_\n      // \\\\";
 	fout.close();
	std::cout << bureaucrat.getName() << " successfully created a shrubbery" << std::endl;
}

Form	*ShrubberyCreationForm::makeForm(Form *form, std::string const &type, std::string const &target)
{
	if (form == NULL && type == "shrubbery creation")
		return (new ShrubberyCreationForm(target));
	return (form);
}

std::string const	&ShrubberyCreationForm::getTarget(void) const
{
	return (this->_target);
}

std::ostream	&operator<<(std::ostream &str, ShrubberyCreationForm const &form)
{
	return (str << form.getName() << " form, signed: " << form.getIsSigned() << ", sign grade: " << form.getSignGrade() << ", exec grade: " << form.getExecGrade());
}
