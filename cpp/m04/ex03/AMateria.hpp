/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:34:03 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/05 18:25:29 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include "ICharacter.hpp"
# include <iostream>

class ICharacter;

class AMateria
{
	protected:
		std::string type;
	public:
		AMateria();
		AMateria(std::string const & t);
		AMateria(AMateria const & s);
		virtual ~AMateria();
		std::string const & getType() const;
		virtual AMateria*   clone() const = 0;
		virtual void        use(ICharacter& t);
};

#endif
