/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:15:33 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/21 12:17:42 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funtions.hpp"

int		main(void)
{
	srand(time(NULL));
	Base	*base = generate();
	identify(base);
	identify(*base);
	delete base;
	return (0);
}

