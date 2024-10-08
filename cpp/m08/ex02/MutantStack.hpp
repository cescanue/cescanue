/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:21:57 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/16 10:58:22 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <iostream>
#include <algorithm>
#include <list>
#include <stack>
#include <deque>

template< typename T>
class MutantStack : public std::stack< T >
{
private:

public:
    MutantStack( void ) {};
    ~MutantStack( void ) {};
    MutantStack( const MutantStack& rhs ) { *this = rhs; }
    MutantStack&    operator=( const MutantStack& rhs ) {
        std::stack< T >::operator=( rhs );
        return *this;
    }
	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
	typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

    iterator    begin() { return this->c.begin(); }
    iterator    end() { return this->c.end(); }
	const_iterator	end() const { return (this->c.end()); }
	iterator rbegin() { return (this->c.rbegin()); }
	const_iterator rbegin() const { return (this->c.rbegin()); }
	iterator rend() { return (this->c.rend()); 	}
	const_iterator rend() const { return (this->c.rend()); }
};

#endif

