/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_philo_eat_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:44:21 by cescanue          #+#    #+#             */
/*   Updated: 2023/06/29 18:30:08 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philosophers_bonus.h"

void	philo_eat(t_philo *d)
{
	sem_wait(d->forks);
	sem_wait(d->m_alive);
	if (d->alive)
		ft_print("has taken a fork", d);
	sem_post(d->m_alive);
	sem_wait(d->forks);
	if (d->alive)
		ft_print("has taken a fork", d);
	sem_post(d->m_alive);
	d->last_time_eat = get_time_ms();
	sem_wait(d->m_alive);
	if (d->alive)
		ft_print("is eating", d);
	sem_post(d->m_alive);
	ft_msleep(d->time_to_eat);
	d->number_of_times_must_eat++;
	sem_post(d->forks);
	sem_post(d->forks);
}
