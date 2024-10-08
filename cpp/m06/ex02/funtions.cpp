/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funtions.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:07:08 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/21 12:12:01 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funtions.hpp"

Base	*generate(void)
{
	int		i;

	i = rand() % 3;
	if (i == 0)
		return (new A);
	else if (i == 1)
		return (new B);
	else
		return (new C);
}

void	identify(Base *p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
}

void	identify(Base &p)
{
	try {
		A &a = dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		(void)a;
	}
	catch (std::exception &e) {
		try {
			B &b = dynamic_cast<B&>(p);
			std::cout << "B" << std::endl;
			(void)b;
		}
		catch (std::exception &e) {
			try {
				C &c = dynamic_cast<C&>(p);
				std::cout << "C" << std::endl;
				(void)c;
			}
			catch (std::exception &e) {
				std::cout << "Error" << std::endl;
			}
		}
	}
}






