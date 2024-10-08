/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:12:07 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/08 11:18:20 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <iostream>
#include <string>

class RPN
{
	public:
		static void calculate(int argc, char **argv);
	private:
		RPN(void);
		RPN(const RPN& to_copy);
		RPN& operator=(const RPN& to_copy);
		~RPN(void);
};

#endif
