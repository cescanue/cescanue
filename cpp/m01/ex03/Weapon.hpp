/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:26:59 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 21:13:44 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_H
# define WEAPON_H

# include <iostream>

class Weapon
{
	private:
		std::string	type;
	public:
		Weapon(std::string type);
		Weapon();
		Weapon(const Weapon &cw);
		~Weapon();
		const	std::string	&getType(void);
		void	setType(std::string type);
};

#endif
