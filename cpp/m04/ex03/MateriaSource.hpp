/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:54:32 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/05 19:04:17 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "AMateria.hpp"
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
    private:
        AMateria*       materias[4];
		AMateria		*todel[500];
		void			savetodel(AMateria *tmp);
    public:
        MateriaSource();
        ~MateriaSource();
        MateriaSource( MateriaSource const & );
        MateriaSource&  operator=( MateriaSource const & );
        AMateria*       getMateria( std::string const & t );
        AMateria*       createMateria( std::string const & t );
        void            learnMateria( AMateria* );
};

#endif
