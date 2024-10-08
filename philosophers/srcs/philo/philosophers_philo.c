/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_philo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:48:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 15:13:57 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_print(char *str, t_philo *d)
{
	pthread_mutex_lock(d->print);
	printf("%ld %d %s\n", get_time_ms() - d->time_init, d->id + 1, str);
	pthread_mutex_unlock(d->print);
}

void	ft_msleep(long ms)
{
	long	ftime;

	ftime = get_time_ms();
	while (get_time_ms() - ftime < ms)
		usleep(10);
}

void	ft_create_philo(t_data *d)
{
	int	count;
	int	nt;

	pthread_mutex_lock(d->start);
	count = -1;
	nt = 0;
	while (++count < d->number_of_philosophers && count == nt)
		if (!pthread_create(&d->th_philos[count],
				0, *philo, &d->d_philo[count]))
			nt++;
	if (count != nt)
	{
		ft_error("Not all threads could be created", d);
	}
	pthread_mutex_unlock(d->start);
}

void	*philo(void *dd_philo)
{
	t_philo	*d;

	d = dd_philo;
	pthread_mutex_lock(d->start);
	pthread_mutex_unlock(d->start);
	d->last_time_eat = get_time_ms();
	while (d->alive)
	{
		philo_eat(d);
		pthread_mutex_lock(d->m_alive);
		if (d->alive)
			ft_print("is sleeping", d);
		pthread_mutex_unlock(d->m_alive);
		ft_msleep(d->time_to_sleep);
		pthread_mutex_lock(d->m_alive);
		if (d->alive)
			ft_print("is thinking", d);
		pthread_mutex_unlock(d->m_alive);
	}
	return (0);
}
