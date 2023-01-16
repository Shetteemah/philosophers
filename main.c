/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:51:42 by sheali            #+#    #+#             */
/*   Updated: 2023/01/16 10:13:28 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ft_usleep is a function that sleeps for a specified amount of time.
// It takes a time in microseconds (time) as an argument and delays the
// execution of the program for that amount of time. It returns 0.
int	ft_usleep(long long time)
{
	long long	begin;

	begin = ft_get_time();
	while ((ft_get_time() - begin) < time)
		usleep(time / 10);
	return (0);
}

// if_one_philo is a function that is called if there is only one philosopher.
// It creates a thread for the philosopher and then waits for the philosopher to
// die. It then frees the memory allocated to the data struct and returns 0.
// The use of ft_usleep here is to delay the execution of the program for 0
// microseconds. if the execution of the program is not delayed, the program
// will exit before the thread is created.
int	if_one_philo(t_data *data)
{
	data->start_time = ft_get_time();
	if (pthread_create(&data->thread_id[0], NULL, \
	&exec_action, &data->philos[0]))
		return (1);
	pthread_detach(data->thread_id[0]);
	while (data->dead == 0)
		ft_usleep(0);
	ft_free(data);
	return (0);
}

// parse_argc is a function that checks if the arguments are valid. It checks
// if the number of arguments is between 5 and 6, if the number of philosophers
// is less than 200, and if all the arguments are numeric. It takes the number
// of arguments (argc) and the arguments (argv) as arguments and returns 0 if
// the arguments are valid, and 1 if they are not.
int	parse_argc(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	if (ft_atoi(argv[1]) > 200)
	{
		ft_putstr("😡 This is a fine restaurant not a music festival, "
			"our tables accomodate only up to 200 philosophers!\n");
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0 || ft_strnumeric(argv[i]) <= 0)
			return (ft_error(NULL));
		++i;
	}
	return (0);
}

// main is the main function of the program. It calls the parse_argc function to
// check the arguments, the ft_init function to initialize the data struct, the
// if_one_philo function if there is only one philosopher, the ft_init_thread
// function to create the threads, and the ft_free function to free the memory
// allocated to the data struct. It returns 0 if the program runs successfully
// and 1 if an error occurs.
int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_argc(argc, argv))
		return (1);
	if (ft_init(&data, argc, argv))
		return (1);
	if (data.philo_n == 1)
		return (if_one_philo(&data));
	if (ft_init_thread(&data))
		return (1);
	ft_free(&data);
	return (0);
}
