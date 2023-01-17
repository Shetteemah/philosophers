/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:52:01 by sheali            #+#    #+#             */
/*   Updated: 2023/01/17 18:36:13 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// this program creates one fork for each philosopher by initializing the mutex
// for each fork. The first fork is initialized with the last fork, meaning that
// the first philosopher will use the last fork as its right fork, and the last
// and the rest
// of the forks are initialized with the previous fork.

// ft_get_time is a function that returns the current time in milliseconds 
// using the gettimeofday function, which is a function that returns the current
// time in seconds and microseconds. We multiply the seconds by 1000 to get the
// time in milliseconds, and then divide the microseconds by 1000 to get the
// time in milliseconds.
long int	ft_get_time(void)
{
	struct timeval	time_val;

	if (gettimeofday(&time_val, NULL))
		return (1);
	return ((time_val.tv_sec * 1000) + (time_val.tv_usec / 1000));
}

// check_chow_xn is a function that checks if all philosophers have eaten the
// number of times specified by the user by checking if the data->finished
// variable is equal to the number of philosophers. If so, it prints a message
// to the screen and sets data->dead variable to 1, which will cause the program
// to exit. The function also checks if a philosopher has died by checking if
// the data->dead variable is equal to 1. If so, it returns 0, which will cause
// the thread to exit.
void	*check_chow_xn(void *data)
{
	int		exit;
	t_philo	*philo;

	philo = (t_philo *) data;
	pthread_mutex_lock(&philo->data->write);
	printf("data val: %d", philo->data->dead);
	pthread_mutex_unlock(&philo->data->write);
	exit = 0;
	while (!exit)
	{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finished >= philo->data->philo_n)
		{
			pthread_mutex_lock(&philo->data->write);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->write);
			exit = 1;
		}
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

// death_checker is a function that checks if a philosopher has died by checking
// if the current time is greater than the time a philosopher should die. If so,
// it prints a message to the screen and sets data->dead variable to 1, which
// will cause the program to exit. The function also checks if a philosopher has
// eaten the number of times specified by the user. If so, it sets data->dead
// variable to 1, which will cause the program to exit. we increment the
// finished variable by 1 to indicate that a philosopher has finished eating.
void	*death_checker(void *philo_ptr)
{
	int		exit;
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	exit = 0;
	while (!exit)
	{
		pthread_mutex_lock(&philo->lock);
		if (ft_get_time() >= philo->time_to_die && philo->eating == 0)
			print_message(DIED, philo);
		if (philo->eat_count == philo->data->max_eat_count)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_lock(&philo->data->write);
		exit = philo->data->dead;
		pthread_mutex_unlock(&philo->data->write);
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

// exec_action is a function that executes the philosopher's actions by calling
// the ft_chow function. It also creates a thread that checks if a philosopher
// has died by checking if the current time is greater than the time a
// philosopher should die. If so, it prints a message to the screen and sets
// data->dead variable to 1, which will cause the program to exit. The function
// also checks if a philosopher has eaten the number of times specified by the
// user. If so, it sets data->dead variable to 1, which will cause the program
// to exit.
void	*exec_action(void *philo_ptr)
{
	int		exit;
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = philo->data->time_to_die + ft_get_time();
	if (pthread_create(&philo->thread, NULL, &death_checker, (void *)philo))
		return ((void *)1);
	exit = 0;
	while (!exit)
	{
		ft_chow(philo);
		print_message(THINKING, philo);
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->data->write);
		exit = philo->data->dead;
		pthread_mutex_unlock(&philo->data->write);
		pthread_mutex_unlock(&philo->lock);
	}
	if (pthread_join(philo->thread, NULL))
		return ((void *)1);
	return ((void *)0);
}

// ft_init_thread is a function that creates a thread that checks if all
// philosophers have eaten the number of times specified by the user by checking
// if the data->finished variable is equal to the number of philosophers. If so,
// it prints a message to the screen and sets data->dead variable to 1, which
// will cause the program to exit. The function also checks if a philosopher has
// died by checking if the data->dead variable is equal to 1. If so, it returns
// 0, which will cause the thread to exit. It then creates a thread for each of
// the philosophers and executes the exec_action function for each thread
// created and passes the address of the philosopher to the function.
int	ft_init_thread(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = -1;
	data->start_time = ft_get_time();
	if (data->max_eat_count > 0)
	{
		if (pthread_create(&t0, NULL, &check_chow_xn, &data->philos[0]))
			return (ft_error(data));
	}
	while (++i < data->philo_n)
	{
		if (pthread_create(&data->thread_id[i], NULL, &exec_action, \
		&data->philos[i]))
			return (ft_error(data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->philo_n)
	{
		if (pthread_join(data->thread_id[i], NULL))
			return (ft_error(data));
	}
	return (0);
}
