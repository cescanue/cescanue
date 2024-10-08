/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:36:38 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 21:15:35 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main ( void ) 
{
  	ScavTrap Carlos( "Carlos" );
    ScavTrap Carlos2( Carlos );

    Carlos.attack( "all" );
    Carlos.takeDamage( 10 );
    Carlos.beRepaired( 10 );
    Carlos.guardGate();
    return 0;
}
