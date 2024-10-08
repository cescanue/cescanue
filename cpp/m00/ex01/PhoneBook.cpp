/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:25:54 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/26 16:30:27 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook(void)
{
	this->index = 0;
	return;
}

int	PhoneBook::main(void)
{
	std::string	cmd;
	std::cout << "Welcome to PhoneBook of Cescanue" << std::endl;
	while (cmd.empty() || (cmd.compare("exit") && cmd.compare("EXIT")))
	{
		std::cout << "Write command (ADD, SEARCH or EXIT):";
		std::getline(std::cin, cmd);
		if (!cmd.compare("add") || !cmd.compare("ADD"))
			this->Add();
		else if (!cmd.compare("search") || !cmd.compare("SEARCH"))
			this->Search();
	}
	return (0);
}

void	PhoneBook::Search(void)
{
	std::string	snbr;
	int			nbr;
	
	this->PrintContacts();
	std::cout << "Which contact would like to see the details (0 to 7):";
	std::getline(std::cin, snbr);
	try
	{
		nbr = std::stoi(snbr);
	}
	catch(...)
	{
		std::cout << "You have to write a number." << std::endl;
	}
	if (nbr < 0 || nbr > 7)
		std::cout << "The indicated index is outside the agenda limits (0 to 7)." << std::endl;
	else
		this->PrintContact(nbr);
}

void	PhoneBook::PrintContact(int nbr)
{
	std::cout << "First Name: " << this->contacts[nbr].GetFirstName() << std::endl;
	std::cout << "Last Name: " << this->contacts[nbr].GetLastName() << std::endl;
	std::cout << "Nick Name: " << this->contacts[nbr].GetNickName() << std::endl;
	std::cout << "Phone Number: " << this->contacts[nbr].GetPhoneNumber() << std::endl;
	std::cout << "Darkest Secrect: " << this->contacts[nbr].GetDarkestSecret() << std::endl;
}

void	PhoneBook::PrintContacts()
{
		int	count;

		count = 0;
		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "|   Index  | Fistname | LastName | NickName |" << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
		while (count < 8)
		{
			std::cout << "|";
			std::cout << std::setw(10);	
			std::cout << count;
			std::cout << "|";
			if (this->contacts[count].GetFirstName().length() < 10)
				std::cout << std::setw(10) << this->contacts[count].GetFirstName();
			else
				std::cout << this->contacts[count].GetFirstName().substr(0, 9) << ".";
			std::cout << "|";
			if (this->contacts[count].GetLastName().length() < 10)
				std::cout << std::setw(10) << this->contacts[count].GetLastName();
			else
				std::cout << this->contacts[count].GetLastName().substr(0, 9) << ".";
			std::cout << "|";
			if (this->contacts[count].GetNickName().length() < 10)
				std::cout << std::setw(10) << this->contacts[count].GetNickName();
			else
				std::cout << this->contacts[count].GetNickName().substr(0, 9) << ".";
			std::cout << "|" << std::endl;
			count++;
		}
		std::cout << "---------------------------------------------" << std::endl;
}

void	PhoneBook::Add(void)
{
	if (this->index < 8)
		this->contacts[this->index++].AddContact();
	else
	{
		this->RotateContacts();
		this->contacts[7].AddContact();
	}
}

void	PhoneBook::RotateContacts()
{
	int	count;

	count = 0;
	while (count < 7)
	{
		this->contacts[count] = this->contacts[count + 1];
		count++;
	}
}
