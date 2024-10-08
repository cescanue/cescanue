/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:48:44 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/26 15:53:15 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void	Contact::AddContact(void)
{
	this->AddFirstName();
	this->AddLastName();
	this->AddNickName();
	this->AddPhoneNumber();
	this->AddDarkestsecret();
}

void	Contact::AddFirstName(void)
{
	std::string	str;

	while (str.empty())
	{
		std::cout << "First Name:";
		std::getline(std::cin, str);
	}
	this->firstname = str;
}

void	Contact::AddLastName(void)
{
	std::string	str;

	while (str.empty())
	{
		std::cout << "Last Name:";
		std::getline(std::cin, str);
	}
	this->lastname = str;
}

void	Contact::AddNickName(void)
{
	std::string	str;

	while (str.empty())
	{
		std::cout << "Nick Name:";
		std::getline(std::cin, str);
	}
	this->nickname = str;
}

void	Contact::AddPhoneNumber(void)
{
	std::string	str;

	while (str.empty())
	{
		std::cout << "Phone Number:";
		std::getline(std::cin, str);
	}
	this->phonenumber = str;
}

void	Contact::AddDarkestsecret(void)
{
	std::string	str;

	while (str.empty())
	{
		std::cout << "Darkest Secret:";
		std::getline(std::cin, str);
	}
	this->darkestsecret = str;
}

std::string	Contact::GetFirstName(void)
{
	return this->firstname;
}

std::string	Contact::GetLastName(void)
{
	return this->lastname;
}

std::string	Contact::GetNickName(void)
{
	return this->nickname;
}

std::string	Contact::GetPhoneNumber(void)
{
	return this->phonenumber;
}

std::string	Contact::GetDarkestSecret(void)
{
	return this->darkestsecret;
}

