/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	curr_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	wait_to_time(t_philo *phil, long sleep_to_time_ms)
{
	long	start;
	long	now;

	start = phil->data->time_start;
	now = curr_time();
	while (now < start + sleep_to_time_ms)
	{
		usleep(50);
		now = curr_time();
	}
	return (0);
}

int	wait_begin(t_philo *philo)
{
	long	first;
	long	second;
	long	third;

	first = START_MS;
	second = START_MS + philo->data->time_to_eat;
	third = START_MS * 2 + philo->data->time_to_eat;
	if (philo->data->num_of_phil == 1)
		wait_to_time(philo, first);
	else if (philo->id % 2 == 0)
		wait_to_time(philo, second);
	else if (philo->id == philo->data->num_of_phil)
		wait_to_time(philo, third);
	else if (philo->id % 2)
		wait_to_time(philo, first);
	return (0);
}
