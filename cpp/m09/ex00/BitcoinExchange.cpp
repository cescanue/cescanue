/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:07:52 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/16 11:06:01 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(std::string btcdb, std::string btc)
{
	this->LoadBTCDb(btcdb);
	this->Check(btc);
}

void	BitcoinExchange::LoadBTCDb(std::string btcdb)
{
	std::string line;
    size_t delim;
	std::ifstream input(btcdb, std::ifstream::in);

	if (!input.is_open())
		throw std::runtime_error(std::string("Error: Unable to open the BTC database -> ") + btcdb);
	std::getline(input, line);
	while (std::getline(input, line))
	{
		delim = line.find(',');
		this->_dataBase.insert(std::pair<std::string, float>(line.substr(0, delim), stof(line.substr(delim + 1))));
	}
	input.close();
	return ;
}

void	BitcoinExchange::Check(std::string btc)
{
	std::string line;
	size_t delim;
	std::ifstream input(btc, std::ifstream::in);

	if (!input.is_open())
		throw std::runtime_error(std::string("Error: could not open file: " + btc));
	if (input.peek() == std::ifstream::traits_type::eof()) 
		throw std::runtime_error(std::string("Error: file:" + btc + " is empty"));
	while (std::getline(input, line))
	{
		if (line == "date | value")
			continue;
		delim = line.find('|');
		if (delim == std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
		std::string date = trim(line.substr(0, delim));
        std::string value = trim(line.substr(delim + 1));
		if (!this->isDateInCorrectFormat(date) || !this->isValidDate(date) || !this->isRateInCorrectFormat(value))
			continue;
		if (this->_dataBase.find(date) != this->_dataBase.end())
			std::cout << date << " => " << value << " = " << (this->_dataBase.find(date))->second * stof(value) << std::endl;
		else
			std::cout << date << " => " << value << " = " << (--this->_dataBase.lower_bound(date))->second * stof(value) << std::endl;
	}
	input.close();
	return ;
}

bool BitcoinExchange::isDateInCorrectFormat(const std::string &date)
{
	if (date.empty())
		return false;

 	size_t first_hyphen = date.find('-');
    size_t second_hyphen = date.find('-', first_hyphen + 1);

	if (first_hyphen == std::string::npos || second_hyphen == std::string::npos
	||  date.find_first_not_of("0123456789.-") != std::string::npos)
	{
		std::cout << BAD_INPUT_ERR << "\"" << date << "\"" << '\n';
		return false;
	}
	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
	std::string s;
	int year, month, day;
	std::istringstream ss(date);
	int i = 0;

	while (std::getline(ss, s, '-'))
	{
		if (i == 0)
		{
			year = stoi(s);
			if (year < 2009 || year > 2022)
			{
				std::cout << YEAR_NOT_ON_DB_ERR << "\"" << date << "\"" << '\n';
				return false;
			}
		}
		if (i == 1)
		{
			month = stoi(s);
			if (month < 1 || month > 12)
			{
				std::cout << INCORRECT_MONTH_ERR << "\"" << date << "\"" << '\n';
				return false;
			}
		}
		if (i == 2)
		{
			day = stoi(s);
			if ((day < 1 || day > 31)
			||  (day == 31 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11))
			||  (day > 28 && month == 2))
			{
				std::cout << INCORRECT_DAY_ERR << "\"" << date << "\"" << '\n';
				return false;
			}
		}
		i += 1;
	}
	if (i != 3 || year * 10000 + month * 100 + day < 20090102)
	{
		std::cout << DATE_NOT_ON_DB_ERR << "\"" << date << "\"" << '\n';
		return false;
	}
	return true;
}

bool BitcoinExchange::isRateInCorrectFormat(const std::string& rate)
{
	if (rate.empty() || rate.find_first_not_of("0123456789.-") != std::string::npos
	||  rate.at(0) == '.' || rate.find('.', rate.length() - 1) != std::string::npos)
		std::cout << INVALID_RATE_ERR << "\"" << rate << "\"" << '\n';
	else if (rate.at(0) == '-')
		std::cout << NOT_A_POSITIVE_ERR << '\n';
	else if (rate.length() > 10 || (rate.length() == 10 && rate > "2147483647"))
		std::cout << TOO_LARGE_ERR << '\n';
	else if (stof(rate) > 1000 || stof(rate) < 0.0001)
		std::cout << INVALID_RATE_ERR << "\"" << rate << "\" valid rate need to be between 0 and 1000" << '\n';
	else
		return true;
	return false;
}

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::~BitcoinExchange(void)
{
	return ;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	*this = src;
	return ;
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	(void) rhs;
	return (*this);
}

std::string BitcoinExchange::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

