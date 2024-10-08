/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:48:17 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/21 10:57:03 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void)
{
	return;
}

ScalarConverter::~ScalarConverter(void)
{
	return;
}

ScalarConverter::ScalarConverter(ScalarConverter const &src)
{
	*this = src;
	return;
}

ScalarConverter	&ScalarConverter::operator=(ScalarConverter const &rhs)
{
	static_cast<void>(rhs);
	return (*this);
}

void	ScalarConverter::Convert(std::string const &str)
{
	if (!str.size())
		throw ScalarConverterException();
	else
		checkType(str);
}

void	ScalarConverter::checkType(std::string const &str)
{
	std::string s;
	double d;
	
	s = str;
	d = atof(s.c_str());
	if (s.size() > 1)
		while (s.find(" ") != std::string::npos)
			s.erase(s.find(" "), 1);
	if (!s.size())
		throw ScalarConverterException();
	else if (s.find("nan") != std::string::npos || s.find("nanf") != std::string::npos || s.find("inf") != std::string::npos || s.find("inff") != std::string::npos || s.find("+inf") != std::string::npos || s.find("+inff") != std::string::npos || s.find("-inf") != std::string::npos || s.find("-inff") != std::string::npos)
	{
		if (s.find("f") != std::string::npos)
			printfloat(s);
		else
			printdouble(s);
	}
	else if (s.size() > 1 && (s.c_str()[0] == '-' || s.c_str()[0] == '+') && !isnumber(s.c_str()[1]))
		throw ScalarConverterException();
	else if (s.size() > 1 && s.c_str()[0] != '-' && s.c_str()[0] != '+' && !isnumber(s.c_str()[0]))
		throw ScalarConverterException();
	else if (s.size() == 1 && !isnumber(s.c_str()[0]))
		printchar(s);
	else if (s.find(".") != std::string::npos)
	{
		if (s.find("f") != std::string::npos)
			printfloat(s);
		else
			printdouble(s);
	}
	else if (d > INT_MAX || d < INT_MIN)
		printdouble(s);
	else
		printint(s);
	return;
}

void	ScalarConverter::printchar(std::string const &str)
{
	int i = (int) str.c_str()[0];
	float f = (float) str.c_str()[0];
	double d = (double) str.c_str()[0];

	if (str.c_str()[0] < 32 || str.c_str()[0] > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << str.c_str()[0] << "'" << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << f << ".0f" << std::endl;
	std::cout << "double: " << d << ".0" << std::endl;
	return;
}

void	ScalarConverter::printint(std::string const &str)
{
	int	i = atoi(str.c_str());
	char c = static_cast<char>(i);
	float f = static_cast<float>(i);
	double d = static_cast<double>(i);
	
	if (i < 32 || i > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << f << ".0f" << std::endl;
	std::cout << "double: " << d << ".0" << std::endl;
	return;
}

void	ScalarConverter::printfloat(std::string const &str)
{
	float f = static_cast<float>(atof(str.c_str()));
	char c = static_cast<char>(f);
	int i = static_cast<int>(f);
	double d = static_cast<double>(f);
	
	if (str.find("nan") != std::string::npos || str.find("nanf") != std::string::npos)
		std::cout << "char: impossible" << std::endl;
	else if (str.find("inf") != std::string::npos || str.find("inff") != std::string::npos)
		std::cout << "char: impossible" << std::endl;
	else 
	{
		if (f < 32 || f > 126)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << c << "'" << std::endl;
	}
	if (str.find("nan") != std::string::npos || str.find("nanf") != std::string::npos)
		std::cout << "int: impossible" << std::endl;
	else if (str.find("inf") != std::string::npos || str.find("inff") != std::string::npos)
		std::cout << "int: impossible" << std::endl;
	else if (f > INT_MAX || f < INT_MIN)
		std::cout << "int: impossible" << std::endl; 
	else 
		std::cout << "int: " << i << std::endl;
	std::cout << "float: " << f;
	if (f - static_cast<int>(f) == 0)
		std::cout << ".0";
	std::cout << "f" << std::endl;
	std::cout << "double: " << d;
	if (f - static_cast<int>(f) == 0)
		std::cout << ".0";
	std::cout << std::endl;
	return;
}

void	ScalarConverter::printdouble(std::string const &str)
{
	double d = static_cast<double>(atof(str.c_str()));
	char c = static_cast<char>(d);
	int i = static_cast<int>(d);
	float f = static_cast<float>(d);
	
	if (str.find("nan") != std::string::npos || str.find("nanf") != std::string::npos)
		std::cout << "char: impossible" << std::endl;
	else if (str.find("inf") != std::string::npos || str.find("inff") != std::string::npos)
		std::cout << "char: impossible" << std::endl;
	else 
	{
		if (d < 32 || d > 126)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << c << "'" << std::endl;
	}
	if (str.find("nan") != std::string::npos || str.find("nanf") != std::string::npos)
		std::cout << "int: impossible" << std::endl;
	else if (str.find("inf") != std::string::npos || str.find("inff") != std::string::npos)
		std::cout << "int: impossible" << std::endl;
	else if (d > INT_MAX || d < INT_MIN)
		std::cout << "int: impossible" << std::endl; 
	else
		std::cout << "int: " << i << std::endl;
	std::cout << "float: " << f;
	if (f - static_cast<int>(f) == 0)
		std::cout << ".0";
	std::cout << "f" << std::endl;
	std::cout << "double: " << d;
	if (d - static_cast<int>(d) == 0)
		std::cout << ".0";
	std::cout << std::endl;
	return;
}

const char* ScalarConverter::ScalarConverterException::what() const throw()
{
	return ("Error: Invalid input.");
}
