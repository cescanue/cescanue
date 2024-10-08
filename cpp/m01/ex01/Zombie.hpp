/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:56:51 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/29 20:59:16 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_H
# define ZOMBIE_H

# include <string>
# include <iostream>

class	Zombie
{
	private:
		std::string	zname;
	
	public:
		Zombie(std::string name);
		Zombie();
		Zombie(const Zombie &cz);
		~Zombie();
		void announce( void );
		void setName(std::string name);
};

#endif
