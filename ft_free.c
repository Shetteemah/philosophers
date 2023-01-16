/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 04:11:23 by sheali            #+#    #+#             */
/*   Updated: 2023/01/15 18:45:25 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ft_allocation_init is a function that allocates memory for the threads,
// forks, and philosophers. It takes a pointer to the data structure (t_data)
// as an argument and returns 0 if all the allocations are successful, and 1
// if not.
int	ft_allocation_init(t_data *data)
{
	data->thread_id = malloc(sizeof(pthread_t) * data->philo_n);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	data->philos = malloc(sizeof(t_philo) * data->philo_n);
	if (!data->thread_id || !data->forks || !data->philo_n)
		return (ft_error(data));
	return (0);
}

// free_data is a function that frees the memory allocated to the data struct.
void	free_data(t_data *data)
{
	if (data->thread_id)
		free(data->thread_id);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

// ft_free is a function that frees the memory allocated to the data struct and
// destroys the mutexes. It is called at the end of the program.
void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
		++i;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	free_data(data);
}

// ft_error is a function that is called when an error occurs. It prints an
// error message and frees the memory allocated to the data struct. It then
// returns 1.
int	ft_error(t_data *data)
{
	printf("Error in input\n");
	if (data)
		ft_free(data);
	return (1);
}
