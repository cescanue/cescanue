/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:51:48 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/16 11:42:23 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN& to_copy) {
	*this = to_copy;
}

RPN& RPN::operator=(const RPN& to_copy) {
	(void)to_copy;
	return *this;
}

RPN::~RPN(void) {}

void RPN::calculate(int argc, char **argv)
{
	std::stack<int> stack;
	
	if (argc < 2)
	{
		std::cout << "Error: bad arguments" << std::endl;
		return;
	}
	for (int i = 1; i < argc; i++)
	{
		for (int j = 0; argv[i][j]; j++)
		{
			if (argv[i][j] == ' ')
				continue;
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				stack.push(argv[i][j] - '0');
			else if (std::strlen(&argv[i][j]) > 1 && (argv[1][j] == '-' || argv[1][j] == '+') && (argv[i][j + 1] >= '0' && argv[i][j + 1] <= '9'))
				stack.push(std::atoi(&argv[i][j++]));
			else if (argv[i][j] == '+' || argv[i][j] == '-' || argv[i][j] == '*' || argv[i][j] == '/' || argv[i][j] == '%')
			{
				if (stack.size() < 2)
				{
					std::cout << "Error: bad arguments" << std::endl;
					return;
				}
				int a = stack.top();
				stack.pop();
				int b = stack.top();
				stack.pop();
				if (argv[i][j] == '+')
					stack.push(b + a);
				else if (argv[i][j] == '-')
					stack.push(b - a);
				else if (argv[i][j] == '*')
					stack.push(b * a);
				else if (argv[i][j] == '/')
				{
					if (!a)
						break;
					stack.push(b / a);
				}
				else if (argv[i][j] == '%')
				{
					if (!a)
						break;
					stack.push(b % a);
				}
			}
			else
			{
				std::cout << "Error: bad arguments " << argv[i] << std::endl;
				return;
			}
		}
	}
	if (stack.size() != 1)
	{
		std::cout << "Error: bad arguments" << std::endl;
		return;
	}
		std::cout << (int) stack.top() << std::endl;
	return;
}

