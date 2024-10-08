/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:28:12 by cescanue          #+#    #+#             */
/*   Updated: 2023/12/21 11:58:37 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int		main(void)
{
	Data *data = new Data("Test");
	uintptr_t raw = Serializer::serialize(data);
	Data *data2 = Serializer::deserialize(raw);
	std::cout << "Data name: " << data->getName() << std::endl;
	std::cout << "Data ptr: " << data << std::endl;
	std::cout << "Serialized into: " << raw << std::endl;
	std::cout << "Deserialized into: " << data2 << std::endl;
	std::cout << "Data2 name: " << data2->getName() << std::endl;
	delete data;
	return (0);
}

