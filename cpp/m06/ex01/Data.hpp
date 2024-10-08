/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:15:57 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/21 11:28:00 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

#include <iostream>

class Data {
	private:
		std::string	_name;
	public:
		Data();
		Data(std::string name);
		Data(Data &t);
		~Data();
		Data & operator=(const Data &t);
		std::string	getName() const;
		void	setName(std::string name);
};

#endif
