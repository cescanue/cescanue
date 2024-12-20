/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:36:38 by cescanue          #+#    #+#             */
/*   Updated: 2023/10/03 10:51:28 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Dog.hpp"
#include "Cat.hpp"

#include "WrongCat.hpp"

int main( void )
{
    const AAnimal* j = new Dog();
    const AAnimal* i = new Cat();
    delete j;
    delete i;
    Dog basic;
	{
    	Dog tmp = basic;
	}
    const AAnimal* animals[4] = { new Dog(), new Dog(), new Cat(), new Cat() };
    for ( int i = 0; i < 4; i++ ) {
        delete animals[i];
    }
    return 0;
}
