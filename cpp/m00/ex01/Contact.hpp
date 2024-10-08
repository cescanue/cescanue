/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:26:54 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/26 15:56:05 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_H
# define CONTACT_H

# include <string>
# include <iostream>

class	Contact
{
	private:
			std::string	firstname;
			std::string	lastname;
			std::string	nickname;
			std::string	phonenumber;
			std::string	darkestsecret;
	public:
			void		AddFirstName(void);
			void		AddLastName(void);
			void		AddNickName(void);
			void		AddPhoneNumber(void);
			void		AddDarkestsecret(void);
			std::string	GetFirstName(void);
			std::string	GetLastName(void);
			std::string	GetNickName(void);
			std::string	GetPhoneNumber(void);
			std::string	GetDarkestSecret(void);
			void		AddContact(void);
};

#endif
