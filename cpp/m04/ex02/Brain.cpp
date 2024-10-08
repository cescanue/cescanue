/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:17:04 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 10:19:19 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain( void )
{
    std::cout << "Brain: created." << std::endl;
}

Brain::~Brain( void )
{
    std::cout << "Brain: destroyed." << std::endl;
}

Brain::Brain( const Brain& s )
{
    *this = s;
}

Brain& Brain::operator=( const Brain& s )
{
    std::cout << "Brain: copy called." << std::endl;
    if ( this != &s ) {
        for ( int count = 0; count < 100; count++ ) {
            this->ideas[count] = s.ideas[count];
        }
    }
    return *this;
}
