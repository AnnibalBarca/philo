/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:32:53 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/28 13:47:22 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define THINKING 0
# define EATING 1
# define SLEEPING 2

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DEATH_MSG "died"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					phi_id;
	int					meals_already_eaten;
	long				last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
	bool				is_ready;
	int                 left_idx;
	int                 right_idx;
}						t_philo;

typedef struct s_data
{
	int					num_of_phis;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_meals;
	int					is_running;
	long				start_time;
	pthread_mutex_t		*forks;
	int                 *fork_taken;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		data_mutex;
	int					is_ready;
	t_philo				*philos;
	bool				all_philos_ready;
}						t_data;

int						data_init(t_data *data, int ac, char **av);

int						init_mutexes(t_data *data);

int						init_philosophers(t_data *data);

int						cleanup_mutexes_partial(t_data *data,
							int forks_initialized, int print_initialized,
							int data_initialized);

void					cleanup_all(t_data *data);

long					get_time(void);

int						ft_usleep_ms(long ms, t_data *data);

void					print_status(t_philo *philo, char *msg);

int						run_philo(t_data *data);

void					*philo_routine(void *arg);

void					*monitor_routine(void *arg);

void					take_forks(t_philo *philo);

void					put_forks(t_philo *philo);

void					eat(t_philo *philo);

void					philo_sleep(t_philo *philo);

void					think(t_philo *philo);

#endif