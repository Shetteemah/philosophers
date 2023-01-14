/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 04:55:01 by sheali            #+#    #+#             */
/*   Updated: 2023/01/14 17:42:10 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKE_FORKS "\033[0;35m has taken a fork 🍴\033[0m"
# define THINKING "\033[0;34m is thinking 🤔\033[0m"
# define SLEEPING "\033[0;33m is sleeping 💤\033[0m"
# define EATING "\033[0;32m is eating 🍽️\033[0m"
# define DIED "\033[0;31m died 💀\033[0m"

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	int				id;
	int				eat_count;
	int				status;
	int				eating;
	long int		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*thread_id;
	int				philo_n;
	int				max_eat_count;
	int				dead;
	int				finished;
	t_philo			*philos;
	long int		time_to_die;
	long int		time_to_sleep;
	long int		time_to_eat;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

int			ft_init(t_data *data, int argc, char **argv);
long int	ft_atoi(char *str);
int			ft_strnumeric(char *str);
int			ft_strcmp(const char *s1, const char *s2);

#endif
