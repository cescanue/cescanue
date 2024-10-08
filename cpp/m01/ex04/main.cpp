/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:36:38 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/01 21:33:17 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <sstream>

std::string	replace(std::string str, std::string oldstr, std::string newstr)
{
	int	pos = 0;
	int	pos1 = 0;
	std::string rstr;

	while (str.find(oldstr, pos) != std::string::npos)
	{
		pos = str.find(oldstr, pos);
		rstr += str.substr(pos1, pos - pos1);
		rstr += newstr;
		pos += oldstr.size();
		pos1 = pos;
	}
	rstr += str.substr(pos1, str.size());
	return (rstr);
}

int main(int argc, char **argv)
{
	std::string			str;
	std::string			ofile;
	std::ifstream		inFile;
	std::ofstream		outFile;
	std::stringstream	strStream;
		
	if (argc < 4)
	{
		std::cout << "usage: file old_word new_word" << std::endl;
		return (1);
	}
	inFile.open(argv[1]);
	if (inFile.fail())
	{
		std::cout << "Error: I could not open the file: "  << argv[1] << std::endl;
		return (1);
	}
	ofile = argv[1];
	ofile += ".replace";
	outFile.open(ofile);
	if (outFile.fail())
	{
		std::cout << "Error: I could not open the file: "  << ofile << std::endl;
		return (1);
	}
	strStream << inFile.rdbuf();
	str = strStream.str();
	outFile << replace(str, argv[2], argv[3]);
	inFile.close();
	outFile.close();
	return 0;
}
