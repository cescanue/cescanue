/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:57:20 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/16 21:08:34 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main( void )
{
    std::cout << "---- TEST #1 -----" << std::endl;

    Span sp = Span( 5 );

    sp.addNumber( 2147483647 );
	sp.addNumber( -2147483648 );
	sp.addNumber( 2147483646 );
	sp.addNumber( 4 );
    try {
	std::cout << "sp: " << sp << std::endl;
	std::cout << "longestSpan: " << sp.longestSpan() << std::endl;
    std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
    std::cout << "\n---- TEST #1 -----" << std::endl;
	} catch ( std::exception& e ) {
        std::cout << e.what() << std::endl; 
    }
    try {
        std::list<int>    l( 10000 );
        std::srand( time ( NULL ) );
        std::generate( l.begin(), l.end(), std::rand );
        Span span( l.size() );
        span.addNumber( l.begin(), l.end() );
        std::cout << "Longest span: " << span.longestSpan() << std::endl;
        std::cout << "Shortest span: " << span.shortestSpan() << std::endl;
    } catch ( std::exception& e ) {
        std::cout << e.what() << std::endl; 
    }
    return EXIT_SUCCESS;
}
