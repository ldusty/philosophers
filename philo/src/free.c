/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleaner(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->data_dead_m);
	pthread_mutex_destroy(&data->last_eat_m);
	pthread_mutex_destroy(&data->num_eat_m);
	while (i < data->num_of_phil)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philo_t);
	free(philo);
}

void	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_phil)
	{
		pthread_join(data->philo_t[i], NULL);
		i++;
	}
}
