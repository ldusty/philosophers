/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	errors(int param)
{
	if (param == 1)
	{
		printf("Parameters of program should be only integer and more than 1\n");
		return (0);
	}
	else if (param == 2)
	{
		printf("Numbers of params less than 5 or more than 6\n");
		return (0);
	}
	else if (param == 3)
	{
		printf("Error mutex init\n");
		return (0);
	}
	else if (param == 4)
	{
		printf("Malloc failed\n");
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long int	out;

	out = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' \
		|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		if (out > INT_MAX)
			return (-1);
		out = (out * 10) + (*str - 48);
		++str;
	}
	return (out);
}

int	validate(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (errors(1));
		i++;
	}
	if (i < 4 || i > 5)
		return (errors(2));
	return (1);
}
