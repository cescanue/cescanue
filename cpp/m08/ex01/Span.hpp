/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:53:56 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/10 12:24:29 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <list>
#include <exception>

class Span
{
private:
    std::list<int>  _list;
    unsigned int    _n;
    Span( void );

public:
    Span( unsigned int );
    Span( const Span& );
    ~Span( void );
    Span&               operator=( const Span& );
    void                addNumber( int );
    void                addNumber( std::list<int>::const_iterator, std::list<int>::const_iterator );
    unsigned int        longestSpan( void ) const;
    unsigned int        shortestSpan( void ) const;
    const std::list< int >*   getList( void ) const;
};
std::ostream& operator<<( std::ostream&, const Span& );

#endif

