/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:59:25 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 21:13:19 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

class ClapTrap
{
	protected:
		std::string     name;
		unsigned int    hitPoints;
		unsigned int    energyPoints;
		unsigned int    attackDamage;

		ClapTrap();

	public:
		ClapTrap( std::string name );
		~ClapTrap();

		ClapTrap(const ClapTrap &);
		ClapTrap &operator=(const ClapTrap& rhs);
		void    attack(std::string const& target);
		void    takeDamage(unsigned int amount);
		void    beRepaired(unsigned int amount);
};

#endif
