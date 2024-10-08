/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:00:15 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 21:46:29 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_clearmen_mutex(t_data *d)
{
	int	count;

	count = -1;
	while (d->d_philo && d->number_of_philosophers > 1
		&& ++count < d->number_of_philosophers)
	{
		if (d->d_philo[count].right_fork)
		{
			pthread_mutex_destroy(d->d_philo[count].right_fork);
			free(d->d_philo[count].right_fork);
			d->d_philo[count].right_fork = 0;
		}
		if (d->d_philo[count].m_alive)
		{
			pthread_mutex_destroy(d->d_philo[count].m_alive);
			free(d->d_philo[count].m_alive);
			d->d_philo[count].m_alive = 0;
		}
	}
}

void	ft_clearmen(t_data *d)
{
	usleep(50);
	ft_clearmen_mutex(d);
	if (d->d_philo)
		free(d->d_philo);
	if (d->th_philos)
		free(d->th_philos);
	if (d->start)
		free(d->start);
	if (d->print)
		free(d->print);
	if (d)
		free(d);
}

void	ft_stop_th(t_data *d)
{
	int	count;

	count = -1;
	while (++count < d->number_of_philosophers)
	{
		if (d->th_philos[count])
		{
			pthread_mutex_lock(d->d_philo[count].m_alive);
			d->d_philo[count].alive = 0;
			pthread_mutex_unlock(d->d_philo[count].m_alive);
		}
	}
}

void	ft_error(char *error, t_data *d)
{
	if (d->th_philos)
		ft_stop_th(d);
	usleep(500);
	printf("Error - %s\n", error);
	ft_clearmen(d);
	exit(0);
}
