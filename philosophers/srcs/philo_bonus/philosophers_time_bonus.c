/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_time_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 09:46:37 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 21:42:16 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philosophers_bonus.h"

int	ft_isone(t_data	*d)
{
	if (d->number_of_philosophers == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(d->time_to_die * 1000 + 100);
		printf("%ld 1 died\n", d->time_to_die + 1);
		return (1);
	}
	else if (d->number_of_philosophers == 0)
		return (1);
	return (0);
}

long	get_time_ms(void)
{
	long			ctime;
	struct timeval	time;

	ctime = 0;
	gettimeofday(&time, NULL);
	ctime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ctime);
}
