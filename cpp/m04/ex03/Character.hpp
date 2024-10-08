/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:39:13 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/05 18:41:11 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

# include <iostream>
# include "ICharacter.hpp"
# include "AMateria.hpp"

class Character : public ICharacter
{
	private:
		std::string name;
		AMateria    *inventory[4];
		AMateria	*todel[500];
		void		savetodel(AMateria *tmp);

	public:
		Character(std::string const &n);
		Character(Character const &s);
		~Character();
		Character&          operator=(Character const &rhs);
		std::string const&  getName() const;
		void                equip(AMateria* m);
		void                unequip(int i);
		void                use(int i, ICharacter& t);
	void	printMaterias( void );
};

#endif
