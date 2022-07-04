/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_time_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_time(philo))
	{
		if (check_eat(philo))
			return (NULL);
		usleep(SLEEP);
	}
	pthread_mutex_lock(&philo->data->data_dead_m);
	if (philo->data->death != 1)
	{
		philo->data->death = 1;
		printf("%lu %d %s", curr_time() - philo->data->time_start - START_MS, \
		philo->id, DEAD);
	}
	pthread_mutex_unlock(&philo->data->data_dead_m);
	return (NULL);
}

void	*philo_alive(void *arg)
{
	t_philo		*philo;
	pthread_t	death_t;

	philo = (t_philo *)arg;
	wait_begin(philo);
	if (pthread_create(&death_t, NULL, check_time_death, philo))
		return (NULL);
	while (check_data_dead(philo, 1))
	{
		if (check_data_dead(philo, 2))
			break ;
		if (take_forks(philo) == 0)
			break ;
		if (eat(philo) == 0)
			break ;
		if (check_data_dead(philo, 2))
			break ;
		if (philo_sleep(philo) == 0)
			break ;
		if (thinking(philo) == 0)
			break ;
	}
	pthread_join(death_t, NULL);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (!validate(&argv[1]))
		return (0);
	init_data(&data, argc, argv);
	if (!init_forks(&data))
		return (0);
	if (!init_philo(&data, &philo))
		return (0);
	join_thread(&data);
	cleaner(&data, philo);
	return (0);
}
