/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:07:57 by sheali            #+#    #+#             */
/*   Updated: 2023/01/17 21:39:40 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// print_message is a function that prints the current time in milliseconds,
// the id of the philosopher and the message of what the philosopher is doing.
// It uses the ft_strcmp function to compare the strings (DIED and str) and if
// they are equal, it will print the message and set the data->dead variable
// to 1, which means that the simulation is over.
void	print_message(char *str, t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->write);
	time = ft_get_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

// take_forks is a function that locks the right fork and the left fork. It	
// uses the philo->right_fork and philo->left_fork mutexes to lock the forks.
// It also prints the message TAKE_FORKS by using the print_message function
// to print the corresponding message of TAKE_FORKS.
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->left_fork);
	print_message(TAKE_FORKS, philo);
}

// drop_forks is a function that unlocks the right fork and the left fork. It
// uses the philo->right_fork and philo->left_fork mutexes to unlock the forks.
// The philosoper will drop the forks after eating. This is done to allow other
// philosophers to eat. If the philosopher does not drop the forks, the other
// philosophers will not be able to eat. This will cause a deadlock.
void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(SLEEPING, philo);
	ft_usleep(philo->data->time_to_sleep);
}

// ft_chow is a function that is used to make the philosopher eat. It uses the
// take_forks function to lock the forks. It also uses the drop_forks function
// to unlock the forks. It also uses the print_message function to print the
// message EATING. It also uses the ft_usleep function to sleep for the time
// specified in the data->time_to_eat variable.
void	ft_chow(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = ft_get_time() + philo->data->time_to_die;
	print_message(EATING, philo);
	philo->eat_count++;
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
