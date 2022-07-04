/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:53 by ldusty            #+#    #+#             */
/*   Updated: 2022/06/24 18:03:54 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

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

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	int			num_of_phil;
	int			death;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		time_start;
	int			max_eat;
	pthread_t	*philo_t;
	t_mutex		*forks;
	t_mutex		last_eat_m;
	t_mutex		data_dead_m;
	t_mutex		num_eat_m;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	long			last_eat;
	int				num_eat;
	int				l_fork;
	int				r_fork;
	int				max_fork;
	int				min_fork;
}	t_philo;

int		validate(char **argv);
int		ft_atoi(const char *str);
int		errors(int flag);
int		init_data(t_data *data, int argc, char **argv);
long	curr_time(void);
int		init_forks(t_data *data);
int		init_philo(t_data *data, t_philo **arg);
int		wait_begin(t_philo *philo);
int		get_l_fork(int i, t_data *data);
int		get_max_fork(t_philo *philo);
int		get_min_fork(t_philo *philo);
void	*philo_alive(void *arg);
int		check_time(t_philo *philo);
int		check_eat(t_philo *philo);
int		check_data_dead(t_philo *philo, int param);
int		get_status(t_philo *philo, char *str);
int		take_forks(t_philo *philo);
int		eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		thinking(t_philo *philo);
void	join_thread(t_data *data);
void	cleaner(t_data *data, t_philo *philo);
#endif
