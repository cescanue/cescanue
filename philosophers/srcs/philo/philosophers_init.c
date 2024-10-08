/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:40:41 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 14:54:22 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_initdata(int argc, char **argv, t_data *d)
{
	d->number_of_times_must_eat = 2147483647;
	d->number_of_philosophers = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		d->number_of_times_must_eat = ft_atoi(argv[5]);
	if (!d->number_of_times_must_eat || !d->time_to_die
		|| !d->time_to_eat || !d->time_to_sleep)
		ft_error("Arguments cannot be 0, it does not make sense.", d);
	d->d_philo = ft_calloc(d->number_of_philosophers, sizeof(t_philo));
	d->th_philos = ft_calloc(d->number_of_philosophers, sizeof(pthread_t));
	d->print = ft_calloc(1, sizeof(pthread_mutex_t));
	d->start = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init (d->print, 0);
	pthread_mutex_init (d->start, 0);
	if (!d->start || !d->print || !d->d_philo || !d->th_philos)
		ft_error("Memory allocation (2)", d);
	if (d->time_to_die < 60 || d->time_to_eat < 60 || d->time_to_sleep < 60)
		ft_error("Times are too low.", d);
	d->time_init = get_time_ms();
}

void	ft_init_philo_data_left_fork(t_data *d)
{
	int	count;

	count = 0;
	while (++count < d->number_of_philosophers)
		d->d_philo[count].left_fork = d->d_philo[count - 1].right_fork;
	d->d_philo[0].left_fork
		= d->d_philo[d->number_of_philosophers - 1].right_fork;
}

void	ft_init_philo_data(t_data *d)
{
	int	count;

	count = -1;
	while (++count < d->number_of_philosophers)
	{
		d->d_philo[count].time_init = d->time_init;
		d->d_philo[count].id = count;
		d->d_philo[count].alive = 1;
		d->d_philo[count].time_to_eat = d->time_to_eat;
		d->d_philo[count].time_to_die = d->time_to_die;
		d->d_philo[count].time_to_sleep = d->time_to_sleep;
		d->d_philo[count].last_time_eat = get_time_ms();
		d->d_philo[count].print = d->print;
		d->d_philo[count].start = d->start;
		d->d_philo[count].right_fork
			= ft_calloc(1, sizeof(pthread_mutex_t));
		d->d_philo[count].m_alive
			= ft_calloc(1, sizeof(pthread_mutex_t));
		if (!d->d_philo[count].right_fork || !d->d_philo[count].m_alive)
			ft_error("Memory allocation (3)", d);
		pthread_mutex_init(d->d_philo[count].right_fork, 0);
		pthread_mutex_init(d->d_philo[count].m_alive, 0);
	}
	ft_init_philo_data_left_fork(d);
}
