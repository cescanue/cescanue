/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:21:08 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/26 16:16:42 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
# define PHONEBOOK_H

# include <string>
# include <iostream>
# include <iomanip>
# include "Contact.hpp"

class	PhoneBook
{
	private:
			int		index;
			Contact contacts[8];
			void	RotateContacts(void);
			void	PrintContacts(void);
			void	PrintContact(int nbr);
	public:
			PhoneBook(void);
			int		main(void);
			void	Add(void);
			void	Search(void);
};

#endif
