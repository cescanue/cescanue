/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:57:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/06 21:03:13 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(void)
{
	std::cout << "Bureaucrat tests:Carlos" << std::endl;
	try
	{
		Bureaucrat Carlos("Carlos", 0);
		std::cout << Carlos << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Bureaucrat tests:Monica" << std::endl;
	try
	{
		Bureaucrat Monica("Monica", 151);
		std::cout << Monica << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Bureaucrat tests:Jesus" << std::endl;
	try 
	{
		Bureaucrat Jesus("Jesus", 3);
		std::cout << Jesus << std::endl;
		Jesus.gradeUp();
		std::cout << Jesus << std::endl;
		Jesus.gradeUp();
		std::cout << Jesus << std::endl;
		Jesus.gradeUp();
		std::cout << Jesus << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "Bureaucrat tests:Alba" << std::endl;
	try 
	{
		Bureaucrat Alba("Alba", 149);
		std::cout << Alba << std::endl;
		Alba.gradeDown();
		std::cout << Alba << std::endl;
		Alba.gradeDown();
		std::cout << Alba << std::endl;
		Alba.gradeDown();
		std::cout << Alba << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
