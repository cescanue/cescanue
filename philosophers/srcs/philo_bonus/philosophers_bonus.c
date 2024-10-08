/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:07:51 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 21:39:20 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philosophers_bonus.h"

void	*check_eats(void *dd)
{
	t_data	*d;
	int		count;

	d = dd;
	count = 0;
	while (count < d->number_of_philosophers)
	{	
		sem_wait(d->eats);
		count++;
	}
	sem_post(d->end);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*d;

	d = calloc(1, sizeof(t_data));
	if (!d)
		ft_error("Memory allocation (1)", d);
	if (argc < 5)
		ft_error("You have not indicated the minimum arguments", d);
	ft_initdata(argc, argv, d);
	if (!ft_isone(d))
	{
		ft_init_philo_data(d);
		ft_create_philo(d);
		pthread_create(&d->check_end, 0, *check_eats, d);
		sem_wait(d->end);
	}
	ft_clearmen(d);
	return (0);
}
