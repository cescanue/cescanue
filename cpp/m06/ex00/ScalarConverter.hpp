/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:48:19 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/21 11:10:21 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <cstdlib>

class ScalarConverter
{
	public:
		static void Convert(std::string const &str);
		class ScalarConverterException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
	private:
		ScalarConverter	&operator=(ScalarConverter const &rhs);
		ScalarConverter(ScalarConverter const &src);
		ScalarConverter(void);
		~ScalarConverter(void);
		static void	checkType(std::string const &str);
		static void printchar(std::string const &str);
		static void printint(std::string const &str);
		static void printfloat(std::string const &str);
		static void printdouble(std::string const &str);
};

#endif
