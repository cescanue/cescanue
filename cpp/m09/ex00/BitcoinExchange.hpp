/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:06:58 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/16 11:05:51 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BitcoinExchange_HPP
# define BitcoinExchange_HPP

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <sstream>
# include <cstdlib>
# include <iomanip>

#define BAD_INPUT_ERR "Error: bad input => "
#define INCORRECT_DATE_ERR "Error: incorrect date => "
#define YEAR_NOT_ON_DB_ERR "Error: year is not at the database => "
#define DATE_NOT_ON_DB_ERR "Error: date is not at the database => "
#define INCORRECT_MONTH_ERR "Error: incorrect month => "
#define INCORRECT_DAY_ERR "Error: incorrect day => "
#define INVALID_RATE_ERR "Error: invalid rate => "
#define NOT_A_POSITIVE_ERR "Error: not a positive number."
#define TOO_LARGE_ERR "Error: too large a number."

class BitcoinExchange
{
	public:
		BitcoinExchange(std::string btcdb, std::string btc);
		~BitcoinExchange(void);
	private:
		void LoadBTCDb(std::string btcdb);
		void Check(std::string btc);
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange	&operator=(const BitcoinExchange &rhs);
		std::map<std::string, float> _dataBase;
		std::string  trim(const std::string& str);
		bool isDateInCorrectFormat(const std::string &date);
        bool isValidDate(const std::string& date);
        bool isRateInCorrectFormat(const std::string& rate);
};

#endif
