/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_error_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:00:15 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 21:49:56 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philosophers_bonus.h"

void	ft_clearmen2(t_data *d)
{
	sem_close(d->print);
	sem_close(d->m_alive);
	sem_close(d->forks);
	sem_close(d->start);
	sem_close(d->end);
	sem_close(d->eats);
	sem_unlink("/print");
	sem_unlink("/start");
	sem_unlink("/end");
	sem_unlink("/eats");
	sem_unlink("/forks");
	sem_unlink("/m_alive");
}

void	ft_clearmen(t_data *d)
{
	int	count;

	count = 0;
	while (count < d->number_of_philosophers && d->number_of_philosophers > 1)
	{
		sem_post(d->eats);
		kill(d->forkpid[count], SIGKILL);
		count++;
	}
	ft_clearmen2(d);
	if (d->d_philo)
		free(d->d_philo);
	if (d->forkpid)
		free(d->forkpid);
	if (d)
		free(d);
	exit(0);
}

void	ft_error(char *error, t_data *d)
{
	printf("Error - %s\n", error);
	ft_clearmen(d);
}
