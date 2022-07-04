/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_max_fork(t_philo *philo)
{
	if (philo->r_fork > philo->l_fork)
		return (philo->r_fork - 1);
	return (philo->l_fork - 1);
}

int	get_min_fork(t_philo *philo)
{
	if (philo->r_fork < philo->l_fork)
		return (philo->r_fork - 1);
	return (philo->l_fork - 1);
}

int	get_l_fork(int i, t_data *data)
{
	if (i == 1)
		return (data->num_of_phil);
	return (i - 1);
}

int	get_status(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->data->data_dead_m);
	time = curr_time();
	if (time - philo->last_eat < philo->data->time_to_die)
	{
		if (philo->data->death == 1)
		{
			pthread_mutex_unlock(&philo->data->data_dead_m);
			return (0);
		}
		printf("%lu %d %s", time - philo->data->time_start - START_MS, \
		philo->id, str);
		pthread_mutex_unlock(&philo->data->data_dead_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->data_dead_m);
	return (0);
}
