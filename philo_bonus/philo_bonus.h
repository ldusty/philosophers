/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

# ifndef CONSTANT
#  define CONSTANT
#  define DELAY_MS 10
#  define DEAD "died\n"
#  define EATING "is eating\n"
#  define SLEEP 250
#  define SLEEPING "is sleeping\n"
#  define START_MS 10
#  define TAKE_FORK "has taken a fork\n"
#  define THINKING "is thinking\n"

# endif

typedef struct s_data
{
	int				num_of_phil;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_start;
	int				max_eat;
	sem_t			*sem_forks;
	sem_t			*sem_last_eat;
	sem_t			*sem_num_eat;
	sem_t			*sem_print;
	pid_t			*arr_pid;
	pthread_t		*philo_thread;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	long			last_eat;
	int				num_eat;
}	t_philo;

int		validate(char **argv);
int		ft_atoi(const char *str);
int		init_data(t_data *data, int argc, char **argv);
long	curr_time(void);
int		ft_exit(t_data *data, int mode, char *str_err);
void	init_forks(t_data *data);
void	*ft_waitpid(void *arg);
void	init_philo(t_data *data);
t_philo	init_philo_struct(t_data *data, int id);
void	wait_begin(t_philo *philo);
int		status(t_philo *philo, char *str);
void	philo_alive(t_data *data, int id);
int		take_forks(t_philo *philo);
int		eating(t_philo *philo);
int		philo_sleeping(t_philo *philo);
int		get_status(t_philo *philo, char *str);
int		thinking(t_philo *philo);

int		first_check_time_death(t_philo *philo);
int		second_check_time_death(t_philo *philo);
int		third_check_time_death(t_philo *philo);
int		check_philo_alive(t_philo *philo, int mode);
#endif