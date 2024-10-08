/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:45:32 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/02 16:50:36 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point( void ) : x(0), y(0) 
{
}

Point::Point( const float x, const float y ) : x(x), y(y) 
{
}

Point::Point( const Point &src ) : x(src.x), y(src.y) 
{
}

Point::~Point() 
{
}

Point&  Point::operator=( const Point &rhs ) 
{
    if ( this != &rhs ) 
	{
        ( Fixed ) this->x = rhs.getX();
        ( Fixed ) this->y = rhs.getY();
    }
    return *this;
}

Fixed Point::getX( void ) const 
{
    return this->x;
}

Fixed Point::getY( void ) const 
{
    return this->y;
}
