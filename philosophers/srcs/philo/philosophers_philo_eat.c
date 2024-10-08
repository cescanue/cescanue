/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_philo_eat.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:44:21 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 15:09:43 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_eat_right(t_philo *d)
{
	pthread_mutex_lock(d->right_fork);
	pthread_mutex_lock(d->m_alive);
	if (d->alive)
		ft_print("has taken right fork", d);
	pthread_mutex_unlock(d->m_alive);
	pthread_mutex_lock(d->left_fork);
	pthread_mutex_lock(d->m_alive);
	if (d->alive)
		ft_print("has taken left fork", d);
	pthread_mutex_unlock(d->m_alive);
}

void	philo_eat_left(t_philo *d)
{
	pthread_mutex_lock(d->left_fork);
	pthread_mutex_lock(d->m_alive);
	if (d->alive)
		ft_print("has taken left fork", d);
	pthread_mutex_unlock(d->m_alive);
	pthread_mutex_lock(d->right_fork);
	pthread_mutex_lock(d->m_alive);
	if (d->alive)
		ft_print("has taken right fork", d);
	pthread_mutex_unlock(d->m_alive);
}

void	philo_eat(t_philo *d)
{
	if (!(d->id % 2))
		philo_eat_right(d);
	else
		philo_eat_left(d);
	d->last_time_eat = get_time_ms();
	pthread_mutex_lock(d->m_alive);
	if (d->alive)
		ft_print("is eating", d);
	pthread_mutex_unlock(d->m_alive);
	ft_msleep(d->time_to_eat);
	d->number_of_times_must_eat++;
	pthread_mutex_unlock(d->right_fork);
	pthread_mutex_unlock(d->left_fork);
}
