/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:36:38 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 21:27:21 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main ( void ) 
{
  	FragTrap Carlos( "Carlos" );
    FragTrap Carlos2( Carlos );

    Carlos.attack( "All" );
    Carlos.takeDamage( 10 );
    Carlos.beRepaired( 10 );
    Carlos.highFive();
    return 0;
}
