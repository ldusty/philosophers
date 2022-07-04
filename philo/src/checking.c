/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->last_eat_m);
	if (curr_time() - philo->last_eat <= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->last_eat_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->last_eat_m);
	return (0);
}

int	check_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->num_eat_m);
	if (philo->data->max_eat != -1 && philo->num_eat == philo->data->max_eat)
	{
		pthread_mutex_unlock(&philo->data->num_eat_m);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->num_eat_m);
		return (0);
	}
}

int	check_data_dead(t_philo *philo, int param)
{
	pthread_mutex_lock(&philo->data->data_dead_m);
	pthread_mutex_lock(&philo->data->num_eat_m);
	if ((param == 1 && \
	(philo->data->death != 1 && philo->num_eat <= philo->data->max_eat)) || \
	(param == 2 && \
	(philo->data->max_eat != -1 && philo->num_eat == philo->data->max_eat)))
	{
		pthread_mutex_unlock(&philo->data->num_eat_m);
		pthread_mutex_unlock(&philo->data->data_dead_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->num_eat_m);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	return (0);
}
