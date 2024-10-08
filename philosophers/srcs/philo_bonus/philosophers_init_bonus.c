/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:40:41 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 21:25:54 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philosophers_bonus.h"

void	ft_initdata2(t_data *d)
{
	d->m_alive = sem_open("/m_alive", O_CREAT, S_IRUSR | S_IWUSR, 1);
	d->print = sem_open("/print", O_CREAT, S_IRUSR | S_IWUSR, 1);
	d->start = sem_open("/start", O_CREAT, S_IRUSR | S_IWUSR, 1);
	d->end = sem_open("/end", O_CREAT, S_IRUSR | S_IWUSR, 1);
	d->eats = sem_open("/eats",
			O_CREAT, S_IRUSR | S_IWUSR, d->number_of_philosophers);
	d->forks = sem_open("/forks",
			O_CREAT, S_IRUSR | S_IWUSR, d->number_of_philosophers);
	if (!d->m_alive || !d->forks || !d->print || !d->start
		|| !d->eats || !d->end || !d->d_philo || !d->forkpid)
		ft_error("Memory allocation (2)", d);
	if (d->time_to_die < 60 || d->time_to_eat < 60 || d->time_to_sleep < 60)
		ft_error("Times are too low.", d);
	d->time_init = get_time_ms();
}

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
	d->forkpid = ft_calloc(d->number_of_philosophers, sizeof(pid_t));
	sem_unlink("/print");
	sem_unlink("/start");
	sem_unlink("/end");
	sem_unlink("/eats");
	sem_unlink("/forks");
	sem_unlink("/m_alive");
	ft_initdata2(d);
}

void	ft_init_philo_data(t_data *d)
{
	int		count;

	count = -1;
	while (++count < d->number_of_philosophers)
	{
		d->d_philo[count].d = d;
		d->d_philo[count].time_init = d->time_init;
		d->d_philo[count].id = count;
		d->d_philo[count].alive = 1;
		d->d_philo[count].time_to_eat = d->time_to_eat;
		d->d_philo[count].time_to_die = d->time_to_die;
		d->d_philo[count].time_to_sleep = d->time_to_sleep;
		d->d_philo[count].last_time_eat = get_time_ms();
		d->d_philo[count].print = d->print;
		d->d_philo[count].start = d->start;
		d->d_philo[count].end = d->end;
		d->d_philo[count].eats = d->eats;
		d->d_philo[count].forks = d->forks;
		d->d_philo[count].m_alive = d->m_alive;
		if (!d->d_philo[count].m_alive)
			ft_error("Memory allocation (3)", d);
	}
}
