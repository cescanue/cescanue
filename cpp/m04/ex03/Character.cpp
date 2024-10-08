/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:40:50 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/06 09:39:01 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character( std::string const & n ) : name(n)
{
    for (int i = 0; i < 4; i++) 
        this->inventory[i] = NULL;
	for (int i = 0; i < 500; i++) 
        this->todel[i] = NULL;
    std::cout << "Character: " << this->name << " created" << std::endl;
}

Character::Character( Character const & s ) : name(s.name)
{
    *this = s;
    std::cout << "Character: " << this->name << " created" << std::endl;
}

Character& Character::operator=( Character const & rhs )
{
    if (this != &rhs)
    {
		this->name = rhs.name;
        for (int i = 0; i < 4; i++)
            this->inventory[i] = rhs.inventory[i];
    }
    return *this;
}

Character::~Character()
{
	for (int i = 0; i < 500; i++)
		if (this->todel[i])
			delete todel[i];
    std::cout << "Character: " << this->name << " destroyed" << std::endl;
}

void	Character::savetodel( AMateria *temp)
{
	int count = 0;
	for ( ; count < 500 && this->todel[count] && this->todel[count] != temp; count ++)
		;
	if (!todel[count])
		todel[count] = temp;
}

void    Character::equip( AMateria* m ) 
{
    if (m)
	{
		for (int i = 0; i < 4; i++)
			if (this->inventory[i] == NULL)
			{
				this->inventory[i] = m;
				this->savetodel(m); 
				std::cout << "Character: " << this->name << " equipped with " << m->getType() << std::endl;
				return;
			}
		std::cout << "Character: " << this->name << " can't equip " << m->getType() << std::endl;
	}
}

void    Character::unequip( int i ) 
{
    if (this->inventory[i])
    {
        this->inventory[i] = NULL;
        std::cout << "Character: " << this->name << " unequipped" << std::endl;
    }
    else
        std::cout << "Character: " << this->name << " can't unequip" << std::endl;
}

void    Character::use( int i, ICharacter& t ) 
{
    if (this->inventory[i])
    {
        this->inventory[i]->use(t);
        std::cout << "Character: " << this->name << " uses " << this->inventory[i]->getType() << std::endl;
    }
    else
        std::cout << "Character: " << this->name << " can't use" << std::endl;
}

std::string const& Character::getName() const 
{
    return this->name;
}


void	Character::printMaterias( void )
{
	for ( int i = 0; i < 4; i++ )
	{
		if ( this->inventory[ i ] != NULL )
			std::cout << "invetory[ " << i << " ] = " << this->inventory[ i ] << std::endl;
		else
			std::cout << "invetory[ " << i << " ] = " << "Empty" << std::endl;
	}
}
