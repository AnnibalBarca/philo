/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:32:53 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/15 18:43:19 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#define THINKING 0
#define EATING 1
#define SLEEPING 2

#define FORK_MSG "has taken a fork"
#define EAT_MSG "is eating"
#define SLEEP_MSG "is sleeping"
#define THINK_MSG "is thinking"
#define DEATH_MSG "died"

typedef struct s_data t_data;

typedef struct s_philo
{
	int phi_id;
	int meals_already_eaten;
	long last_meal_time;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data *data;
} t_philo;

typedef struct s_data
{
	int num_of_phis;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_of_meals;
	int is_running;
	long start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	pthread_mutex_t data_mutex;
	t_philo *philos;
} t_data;

int	data_init(t_data *data, int ac, char **av);



#endif