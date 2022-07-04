/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	take_forks(t_philo *philo)
{
	if (first_check_time_death(philo) != 1)
		return (0);
	sem_wait(philo->data->sem_forks);
	if (get_status(philo, TAKE_FORK) == 0 || philo->data->num_of_phil == 1)
	{
		sem_post(philo->data->sem_forks);
		return (0);
	}
	sem_wait(philo->data->sem_forks);
	if (get_status(philo, TAKE_FORK) == 0)
	{
		sem_post(philo->data->sem_forks);
		sem_post(philo->data->sem_forks);
		return (0);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	long	time;

	if (first_check_time_death(philo) != 1)
		return (0);
	if (get_status(philo, EATING) == 0)
	{
		sem_post(philo->data->sem_forks);
		sem_post(philo->data->sem_forks);
		return (0);
	}
	sem_wait(philo->data->sem_last_eat);
	philo->last_eat = curr_time();
	sem_post(philo->data->sem_last_eat);
	time = curr_time();
	while (curr_time() < time + philo->data->time_to_eat)
		usleep(SLEEP);
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
	sem_wait(philo->data->sem_num_eat);
	if (philo->num_eat != -1)
		philo->num_eat++;
	sem_post(philo->data->sem_num_eat);
	return (1);
}

int	philo_sleeping(t_philo *philo)
{
	long	time;

	if (first_check_time_death(philo) != 1)
		return (0);
	if (second_check_time_death(philo))
		return (0);
	if (get_status(philo, SLEEPING) == 0)
		return (0);
	time = curr_time();
	while (curr_time() < time + philo->data->time_to_sleep)
		usleep(SLEEP);
	return (1);
}

int	thinking(t_philo *philo)
{
	if (first_check_time_death(philo) != 1)
		return (0);
	if (second_check_time_death(philo))
		return (0);
	if (get_status(philo, THINKING) == 0)
		return (0);
	return (1);
}
