/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death_m(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_dead_m);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->data_dead_m);
		return (0);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (check_death_m(philo) == 0)
		return (0);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	pthread_mutex_lock(&philo->data->forks[philo->min_fork]);
	if (get_status(philo, TAKE_FORK) == 0 || philo->data->num_of_phil == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->forks[philo->max_fork]);
	if (get_status(philo, TAKE_FORK) == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
		return (0);
	}
	return (1);
}

int	eat(t_philo *philo)
{
	long	time;

	if (check_death_m(philo) == 0)
		return (0);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	if (get_status(philo, EATING) == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->last_eat_m);
	philo->last_eat = curr_time();
	pthread_mutex_unlock(&philo->data->last_eat_m);
	time = curr_time();
	while (curr_time() < time + philo->data->time_to_eat)
		usleep(50);
	pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
	pthread_mutex_lock(&philo->data->num_eat_m);
	if (philo->num_eat != -1)
		philo->num_eat++;
	pthread_mutex_unlock(&philo->data->num_eat_m);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	long	time;

	if (check_death_m(philo) == 0)
		return (0);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	if (get_status(philo, SLEEPING) == 0)
		return (0);
	time = curr_time();
	while (curr_time() < time + philo->data->time_to_sleep)
		usleep(50);
	return (1);
}

int	thinking(t_philo *philo)
{
	long	time;

	if (check_death_m(philo) == 0)
		return (0);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	if (get_status(philo, THINKING) == 0)
		return (0);
	if (philo->data->time_to_eat > philo->data->time_to_sleep)
	{
		time = curr_time();
		while (curr_time() < time + \
		philo->data->time_to_eat - philo->data->time_to_sleep)
			usleep(10);
	}
	if (philo->data->num_of_phil % 2)
	{
		time = curr_time();
		while (curr_time() < time + DELAY_MS)
			usleep(10);
	}
	return (1);
}
