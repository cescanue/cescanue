/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_philo_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:48:01 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 21:19:18 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philosophers_bonus.h"

void	ft_print(char *str, t_philo *d)
{
	sem_wait(d->print);
	printf("%ld %d %s\n", get_time_ms() - d->time_init, d->id + 1, str);
	sem_post(d->print);
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

	count = -1;
	sem_wait(d->start);
	sem_wait(d->end);
	while (++count < d->number_of_philosophers)
	{
		sem_wait(d->eats);
		d->forkpid[count] = fork();
		if (!d->forkpid[count])
		{
			philo(&d->d_philo[count], d);
			exit(0);
		}
	}
	sem_post(d->start);
}

void	philo2(t_philo *d, t_data *gd)
{
	if (d->alive && get_time_ms()
		- d->last_time_eat
		> d->time_to_die)
	{
		sem_wait(d->m_alive);
		d->alive = 0;
		sem_post(d->m_alive);
		ft_print("died", d);
		sem_post(d->end);
		sem_wait(d->print);
		exit(0);
	}
	if (d->number_of_times_must_eat
		>= gd->number_of_times_must_eat)
	{
		sem_post(d->eats);
		exit(0);
	}
}

void	*philo(t_philo *d, t_data *gd)
{
	sem_wait(d->start);
	sem_post(d->start);
	d->last_time_eat = get_time_ms();
	while (d->alive)
	{
		philo2(d, gd);
		philo_eat(d);
		sem_wait(d->m_alive);
		if (d->alive)
			ft_print("is sleeping", d);
		sem_post(d->m_alive);
		ft_msleep(d->time_to_sleep);
		sem_wait(d->m_alive);
		if (d->alive)
			ft_print("is thinking", d);
		sem_post(d->m_alive);
		philo2(d, gd);
	}
	return (0);
}
