/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:51:22 by sheali            #+#    #+#             */
/*   Updated: 2023/01/14 17:40:48 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ft_fork_init is a function that initializes the forks. It takes a pointer to
// data structure (t_data) as an argument and passes it to pthread_mutex_init
// which initializes the mutex. It takes the pointer that points to the mutex
// (data->forks) and a pointer to the mutex attributes (NULL) as arguments. If
// the mutex attributes are NULL, the default mutex attributes are used, if not,
// the mutex attributes are used. The function returns 0 if the mutex is
// initialized, and 1 if not.
// The first fork is initialized with the last fork, and the rest of the forks
// are initialized with the previous fork.
int	ft_fork_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->philo_n - 1];
	i = 1;
	while (i < data->philo_n)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

// philos_init is a function that initializes the philosophers. It takes a
// pointer to the data structure (t_data) as an argument and initializes the
// philosophers with the data from the data structure. It also initializes the
// mutex lock for each philosopher before moving on to the next philosopher to
// make sure that the philosophers are not initialized with the same data, the
// id of each philosopher is incremented by 1 as it is initialized.
void	philos_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].eat_count = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

// ft_data_init is a function that initializes the data structure. It takes a
// pointer to the data structure (t_data) and the arguments from the command
// line as arguments (argc). It initializes the data structure with the
// arguments from the command line and initializes the mutex lock for the data
// structure to make sure that the data structure is not initialized with the
// same data. It returns 0 if the data structure is initialized, and 1 if not.
int	ft_data_init(t_data *data, int argc, char **argv)
{
	data->philo_n = (int) ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat_count = (int) ft_atoi(argv[5]);
	else
		data->max_eat_count = -1;
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

// ft_init is a function that initializes the data structure, allocates memory
// for the threads, forks, and philosophers, and initializes the forks and the
// philosophers. It takes a pointer to the data structure (t_data) and the
// arguments from the command line as arguments (argc). It returns 0 if the
// data structure, memory allocations, and forks and philosophers are all
// initialized, and 1 if not.
int	ft_init(t_data *data, int argc, char **argv)
{
	if (ft_data_init(data, argc, argv))
		return (1);
	if (ft_allocation_init(data))
		return (1);
	if (ft_fork_init(data))
		return (1);
	philos_init(data);
	return (0);
}
