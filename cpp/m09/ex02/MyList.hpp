/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyList.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:28:42 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/18 21:31:34 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYLIST_HPP
# define MYLIST_HPP

template <typename T>
class	MyList : public std::list<T>
{
	public:
		MyList(void) : std::list<T>() {}
		MyList(MyList const &src) : std::list<T>(src) {}
		~MyList(void) {}
		MyList	&operator=(MyList const &rhs)
		{
			std::list<T>::operator=(rhs);
			return (*this);
		}
		T &operator[](unsigned int n)
		{
			typename std::list<T>::iterator ite = this->begin();
			for (unsigned int i = 0; i < n; i++)
				ite++;
			return (*ite);
		}
		class iterator : public std::list<T>::iterator
		{
			public:
				iterator(void) : std::list<T>::iterator() {}
				iterator(typename std::list<T>::iterator const &src) : std::list<T>::iterator(src) {}
				~iterator(void) {}
				iterator	&operator=(iterator const &rhs)
				{
					std::list<T>::iterator::operator=(rhs);
					return (*this);
				}
				iterator operator+(iterator const &rhs)
				{
					iterator tmp = *this;
					for (int i = 0; i < rhs; i++)
						std::list<T>::iterator::operator++();
					return (tmp);
				}
				iterator operator+(unsigned int n)
				{
					iterator tmp = *this;
					for (unsigned int i = 0; i < n; i++)
						std::list<T>::iterator::operator++();
					return (tmp);
				}
				iterator &operator+=(int n)
				{
					for (int i = 0; i < n; i++)
						std::list<T>::iterator::operator++();
					return (*this);
				}
		};
};

#endif
