/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:57:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/06 21:27:54 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
	std::cout << "Form tests:FormTooHigh" << std::endl;
	try
	{
		Form formtoohigh("TooHigh", 0, 5);
		std::cout << formtoohigh << std::endl;
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << "Form tests:Carlos Form 100" << std::endl;
	try
	{
		Bureaucrat Carlos("Carlos", 15);
		Form form("100", 20, 45);
		std::cout << Carlos << std::endl;
		std::cout << form << std::endl;
		Carlos.signForm(form);
		std::cout << form << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Form tests:Alba Form 101" << std::endl;
	try
	{
		Bureaucrat Alba("Alba", 35);
		Form form2("101", 20, 45);
		std::cout << Alba << std::endl;
		std::cout << form2 << std::endl;
		Alba.signForm(form2);
		std::cout << form2 << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
