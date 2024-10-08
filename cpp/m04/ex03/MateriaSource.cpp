/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:55:16 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/06 09:57:15 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
    for (int i = 0; i < 4; i++)
        materias[i] = NULL;
	for (int i = 0; i < 500; i++) 
        this->todel[i] = NULL;
}

MateriaSource::~MateriaSource()
{
 /*   for (int i = 0; i < 4; i++)
        if (materias[i])
            delete materias[i];
	*/
	for (int i = 0; i < 500 && this->todel[i]; i++)
		delete todel[i];		
}

MateriaSource::MateriaSource(MateriaSource const & s)
{
    *this = s;
}

MateriaSource& MateriaSource::operator=( MateriaSource const & rhs )
{
    if (this != &rhs)
    {
        for (int i = 0; i < 4; i++)
            materias[i] = rhs.materias[i];
    }
    return *this;
}

void	MateriaSource::savetodel( AMateria *temp)
{
	int count = 0;
	for ( ; count < 500 && this->todel[count] && this->todel[count] != temp; count ++)
		;
	if (!todel[count])
		todel[count] = temp;
}

AMateria* MateriaSource::getMateria( std::string const & t )
{
    for (int i = 0; i < 4; i++)
        if (materias[i] && materias[i]->getType() == t)
            return materias[i];
    return NULL;
}

void    MateriaSource::learnMateria( AMateria* m )
{
    for (int i = 0; i < 4; i++)
        if (materias[i] == NULL)
        {
            materias[i] = m;
			this->savetodel( m );
            return;
        }
	std::cout << "MateriaSource: " << m->getType() << " cannot be stored, warehouse full, please be sure to delete it. " << std::endl;
}

AMateria*   MateriaSource::createMateria( std::string const& t ) {
    for ( int i = 0; i < 4; i++ )
        if ( materias[i] && materias[i]->getType() == t )
		{
            AMateria *m = materias[i]->clone();
			return m;
		}
    return NULL;
}
