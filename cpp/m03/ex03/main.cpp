/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:36:38 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 09:30:35 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main ( void ) 
{
  	DiamondTrap Carlos( "Carlos" );
    DiamondTrap Carlos2( Carlos );
    DiamondTrap Carlos3( "Carlos3");

    Carlos.whoAmI();
    Carlos2.whoAmI();
    Carlos3 = Carlos;
    Carlos3.whoAmI();

    Carlos.attack( "all" );
    Carlos.takeDamage( 10 );
    Carlos.beRepaired( 10 );
    return 0;
}
