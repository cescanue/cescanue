/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:07:51 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 20:58:49 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_main1(int *alive, int *eats, t_data *d)
{
	int		count;

	*alive = 0;
	*eats = 0;
	count = -1;
	while (d->th_philos[++count] && count < d->number_of_philosophers)
	{
		if (d->d_philo[count].alive && get_time_ms()
			- d->d_philo[count].last_time_eat
			> d->d_philo[count].time_to_die)
		{
			pthread_mutex_lock(d->d_philo[count].m_alive);
			d->d_philo[count].alive = 0;
			pthread_mutex_unlock(d->d_philo[count].m_alive);
			ft_print("died", &d->d_philo[count]);
			pthread_mutex_lock(d->print);
			exit(0);
		}
		if (d->d_philo[count].alive)
			(*alive)++;
		if (d->d_philo[count].number_of_times_must_eat
			>= d->number_of_times_must_eat)
			(*eats)++;
	}
}

void	philo_main(t_data *d)
{
	int		alive;
	int		eats;

	alive = d->number_of_philosophers;
	eats = 0;
	while (alive == d->number_of_philosophers && eats
		< d->number_of_philosophers)
		philo_main1(&alive, &eats, d);
	pthread_mutex_lock(d->print);
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
	ft_init_philo_data(d);
	ft_create_philo(d);
	philo_main(d);
	ft_clearmen(d);
	return (0);
}
