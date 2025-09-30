/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:36:27 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/30 12:58:43 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philo(t_philo *philo)
{
	think(philo);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK_MSG);
	pthread_mutex_unlock(philo->left_fork);
	usleep(philo->data->time_to_die * 1000);
}

static void	running_routine(t_philo	*philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (!philo->data->is_running)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		think(philo);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		philo_sleep(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_bool(&philo->mutex, &philo->is_ready, true);
	if (philo->data->num_of_phis == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	while (get_int(&philo->data->data_mutex, &philo->data->is_ready) == -1)
		usleep(100);
	if (get_int(&philo->data->data_mutex, &philo->data->is_ready) == 1)
		return (NULL);
	set_long(&philo->mutex, &philo->last_meal_time,
		philo->data->start_time);
	if (philo->phi_id % 2 == 1 && philo->phi_id != philo->data->num_of_phis)
		usleep(philo->data->time_to_eat * 1000);
	running_routine(philo);
	return (NULL);
}
