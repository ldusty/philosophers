/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_time_death(void *arg)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	while (first_check_time_death(philo))
	{
		if (second_check_time_death(philo))
			return (NULL);
	}
	sem_wait(philo->data->sem_print);
	if (third_check_time_death(philo))
	{
		status(philo, DEAD);
		time = curr_time();
		while (curr_time() < time + philo->data->time_to_die + DELAY_MS)
			usleep(SLEEP);
	}
	sem_post(philo->data->sem_print);
	return (NULL);
}

void	philo_alive(t_data *data, int id)
{
	t_philo		philo;
	pthread_t	death_t;

	philo = init_philo_struct(data, id);
	wait_begin(&philo);
	if (pthread_create(&death_t, NULL, check_time_death, &philo))
		exit(ft_exit(data, 2, "Error pthread_create\n"));
	while (check_philo_alive(&philo, 1))
	{
		if (check_philo_alive(&philo, 2))
			break ;
		if (take_forks(&philo) == 0)
			break ;
		if (eating(&philo) == 0)
			break ;
		if (philo_sleeping(&philo) == 0)
			break ;
		if (thinking(&philo) == 0)
			break ;
		if (check_philo_alive(&philo, 2))
			break ;
	}
	pthread_join(death_t, NULL);
	exit(ft_exit(data, 3, ""));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate(&argv[1]))
		return (0);
	init_data(&data, argc, argv);
	init_forks(&data);
	init_philo(&data);
	ft_exit(&data, 3, "");
	return (0);
}
