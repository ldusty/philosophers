/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	status(t_philo *philo, char *str)
{
	long	time;

	time = curr_time() - philo->data->time_start - START_MS;
	printf("%ld %d %s", time, philo->id, str);
	return (0);
}

int	get_status(t_philo *philo, char *str)
{
	sem_wait(philo->data->sem_print);
	if (first_check_time_death(philo))
	{
		status(philo, str);
		sem_post(philo->data->sem_print);
		return (1);
	}
	sem_post(philo->data->sem_print);
	return (0);
}

int	ft_exit(t_data *data, int mode, char *str_err)
{
	printf("%s", str_err);
	if (mode >= 2)
		free(data->arr_pid);
	if (mode >= 3)
	{
		sem_close(data->sem_last_eat);
		sem_close(data->sem_num_eat);
		sem_close(data->sem_print);
		sem_close(data->sem_forks);
	}
	return (0);
}

void	*ft_waitpid(void *arg)
{
	pid_t	*pid;

	pid = (pid_t *)arg;
	waitpid(*pid, NULL, 0);
	return (NULL);
}
