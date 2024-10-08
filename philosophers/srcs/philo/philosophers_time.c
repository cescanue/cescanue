/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_time.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 09:46:37 by cescanue          #+#    #+#             */
/*   Updated: 2023/06/14 09:50:35 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time_ms(void)
{
	long			ctime;
	struct timeval	time;

	ctime = 0;
	gettimeofday(&time, NULL);
	ctime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ctime);
}
