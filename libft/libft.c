/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:53:49 by sheali            #+#    #+#             */
/*   Updated: 2023/01/14 17:41:31 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// ft_atoi is a function that converts a string to an integer.
// It returns the integer value of the string.
long int	ft_atoi(char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * neg);
}

// ft_strnumeric is a function that checks if a string is numeric. It takes a
// string (str) as an argument and returns 1 if it is numeric, and 0 if it is
// not.
int	ft_strnumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (str[i] == '\0')
			return (0);
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (0);
	}
	return (1);
}

// ft_strcmp is a function that compares two strings. It takes two strings
// (s1 and s2) as arguments and returns 0 if they are the same, and a
// non-zero value if they are not.
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// ft_putstr is a function that prints a string. It takes a string (str) as an
// argument and returns the string.
char	*ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (str);
}
