/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	first_check_time_death(t_philo *philo)
{
	sem_wait(philo->data->sem_last_eat);
	if (curr_time() - philo->last_eat <= philo->data->time_to_die)
	{
		sem_post(philo->data->sem_last_eat);
		return (1);
	}
	sem_post(philo->data->sem_last_eat);
	return (0);
}

int	second_check_time_death(t_philo *philo)
{
	sem_wait(philo->data->sem_num_eat);
	if (philo->data->max_eat != -1 && philo->num_eat == philo->data->max_eat)
	{
		sem_post(philo->data->sem_num_eat);
		return (1);
	}
	sem_post(philo->data->sem_num_eat);
	return (0);
}

int	third_check_time_death(t_philo *philo)
{
	sem_wait(philo->data->sem_last_eat);
	if (curr_time() - philo->last_eat - philo->data->time_to_die \
	< DELAY_MS)
	{
		sem_post(philo->data->sem_last_eat);
		return (1);
	}
	sem_post(philo->data->sem_last_eat);
	return (0);
}

int	check_philo_alive(t_philo *philo, int mode)
{
	sem_wait(philo->data->sem_num_eat);
	if ((mode == 1 && \
	(first_check_time_death(philo) \
	&& philo->num_eat <= philo->data->max_eat)) || \
	(mode == 2 && \
	(philo->data->max_eat != -1 && philo->num_eat >= philo->data->max_eat)))
	{
		sem_post(philo->data->sem_num_eat);
		return (1);
	}
	sem_post(philo->data->sem_num_eat);
	return (0);
}
