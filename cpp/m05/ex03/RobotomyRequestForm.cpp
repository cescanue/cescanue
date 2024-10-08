/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:26:31 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/08 21:39:20 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include "Form.hpp"

RobotomyRequestForm::RobotomyRequestForm(void): Form::Form("RobotomyRequestForm", 72, 45), _target("null") {}

RobotomyRequestForm::RobotomyRequestForm(std::string const &target): Form::Form("RobotomyRequestForm", 72, 45), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &copy): Form::Form(copy), _target(copy._target) {}

RobotomyRequestForm::~RobotomyRequestForm(void) {}

RobotomyRequestForm const	&RobotomyRequestForm::operator=(const RobotomyRequestForm &copy)
{
	Form::operator=(copy);
	this->_target = copy._target;
	return (*this);
}

void	RobotomyRequestForm::beExecuted(const Bureaucrat &bureaucrat) const
{
	(void)bureaucrat;
	srand((unsigned) time(NULL));
	if (rand() % 2)
		std::cout << this->_target << " has been robotomized successfully" << std::endl;
	else
		std::cout << this->_target << "'s robotomization failed" << std::endl;
}

Form	*RobotomyRequestForm::makeForm(Form *form, std::string const &type, std::string const &target)
{
	if (form == NULL && type == "robotomy request")
		return (new RobotomyRequestForm(target));
	return (form);
}

std::string const	&RobotomyRequestForm::getTarget(void) const
{
	return (this->_target);
}

std::ostream	&operator<<(std::ostream &str, RobotomyRequestForm const &form)
{
	return (str << form.getName() << " form, signed: " << form.getIsSigned() << ", sign grade: " << form.getSignGrade() << ", exec grade: " << form.getExecGrade());
}
