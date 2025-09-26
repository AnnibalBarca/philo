/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:36:27 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/26 13:47:07 by almeekel         ###   ########.fr       */
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

static int	should_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->num_of_meals > 0
		&& philo->meals_already_eaten >= philo->data->num_of_meals)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (1);
}

static int	is_running(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (!philo->data->is_running)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_phis == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if (philo->phi_id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!is_running(philo))
			break ;
		think(philo);
		take_forks(philo);
		if (!should_eat(philo))
		{
			put_forks(philo);
			break ;
		}
		eat(philo);
		put_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

