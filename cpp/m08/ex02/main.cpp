/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:23:40 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/16 10:48:30 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

template <typename T>
static void displayMutantStack(MutantStack<T>& ms)
{
	std::cout << "{";
	for (typename MutantStack<T>::iterator it = ms.begin(); it != ms.end(); it++)
		std::cout << " " << *it;
	std::cout << " }" << std::endl;
}


int main()
{
    MutantStack<int> mstack;
    std::cout << "/ ***** MutantStack ***** /" << std::endl;
    mstack.push(5);
    mstack.push(17);
    std::cout << mstack.top() << std::endl;
    mstack.pop();
    std::cout << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> ss(mstack);
    std::cout << std::endl;
    std::cout << "/ ***** List ***** /" << std::endl;
    std::list< int > lst;
    lst.push_back(5);
    lst.push_back(17);
    std::cout << lst.back() << std::endl;
    lst.pop_back();
    std::cout << lst.size() << std::endl;
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);
    std::list<int>::iterator lst_it = lst.begin();
    std::list<int>::iterator lst_ite = lst.end();
    ++it;
    --it;
    while (lst_it != lst_ite)
    {
        std::cout << *lst_it << std::endl;
        ++lst_it;
    }
    std::list<int> l(lst);
	MutantStack<int> ms;

	srand(time(NULL));
	for (int i = 0; i < 10; i++)
		ms.push(rand() % 100);
	std::cout << "MutantStack ms: " << std::endl;
	displayMutantStack<int>(ms);
	
	std::cout << std::endl << "Pop three elements out of ms:" << std::endl;
	for (int i = 0; i < 3; i++)
		ms.pop();
	displayMutantStack<int>(ms);

	std::cout << std::endl << "Change first element to 42 using the iterator:" << std::endl;
	*ms.begin() = 42;
	displayMutantStack<int>(ms);

	std::stack<int> s(ms);
	std::cout << std::endl << "Size of ms: " << ms.size() << std::endl;
	std::cout << "Size of s: " << s.size() << std::endl;


    return 0;
}

