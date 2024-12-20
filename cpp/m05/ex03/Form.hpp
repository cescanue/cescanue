/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:09:32 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/08 21:35:32 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>

class Bureaucrat;

class Form
{
	private:
		std::string const	_name;
		bool				_isSigned;
		int const			_signGrade;
		int const			_execGrade;
	public:
		/* Constructors & Destructors */
		Form(void);
		Form(std::string const &name, int const &signGrade, int const &execGrade);
		Form(std::string const &type, std::string const &target);
		Form(Form const &copy);
		virtual ~Form(void);

		/* Basic Operators */
		Form const	&operator=(Form const &copy);

		/* Getters & Setters */
		std::string const			&getName(void) const;
		bool const					&getIsSigned(void) const;
		int const					&getSignGrade(void) const;
		int const					&getExecGrade(void) const;
		virtual std::string const	&getTarget(void) const = 0;

		/* Main Member Functions */
		void			beSigned(Bureaucrat &bureaucrat);
		void			execute(Bureaucrat const &executor) const;
		virtual void	beExecuted(Bureaucrat const &bureaucrat) const = 0;
		static Form		*makeForm(std::string const &type, std::string const &target);

		/* Exceptions */
		class GradeTooHighException: public std::exception
		{
			public:
				virtual char const	*what(void) const throw();
		};
		class GradeTooLowException: public std::exception
		{
			public:
				virtual char const	*what(void) const throw();
		};
		class FormNotSignedException: public std::exception
		{
			public:
				virtual char const	*what(void) const throw();
		};
		class InvalidFormException: public std::exception
		{
			public:
				virtual char const	*what(void) const throw();
		};
};

std::ostream	&operator<<(std::ostream &str, Form const &form);

#endif
