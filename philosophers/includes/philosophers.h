/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:06:11 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/13 14:52:09 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

struct					s_philo;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_must_eat;
	t_philo			*d_philo;
	pthread_t		*th_philos;
	pthread_mutex_t	*print;
	pthread_mutex_t	*start;
	long			time_init;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				alive;
	pthread_mutex_t	*m_alive;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_must_eat;
	long			last_time_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*start;
	long			time_init;
}	t_philo;

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
void	ft_error(char *error, t_data *d);
void	ft_clearmen(t_data *d);
long	get_time_ms(void);
void	ft_init_philo_data(t_data *d);
void	ft_initdata(int argc, char **argv, t_data *d);
void	*philo(void *dd_philo);
void	ft_print(char *str, t_philo *d);
void	ft_create_philo(t_data *d);
void	philo_eat(t_philo *d);
void	ft_msleep(long ms);

#endif