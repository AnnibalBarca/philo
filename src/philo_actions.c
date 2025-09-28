/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:38:20 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/27 18:31:04 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	fork1_idx;
	int	fork2_idx;

	// Get the actual fork indices by comparing memory addresses
	// Find which fork has the lower index in the forks array
	for (fork1_idx = 0; fork1_idx < philo->data->num_of_phis; fork1_idx++)
	{
		if (&philo->data->forks[fork1_idx] == philo->left_fork)
			break;
	}
	for (fork2_idx = 0; fork2_idx < philo->data->num_of_phis; fork2_idx++)
	{
		if (&philo->data->forks[fork2_idx] == philo->right_fork)
			break;
	}

	// Always take the lower-indexed fork first to prevent deadlock
	if (fork1_idx < fork2_idx)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_MSG);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_MSG);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_MSG);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_MSG);
	}
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	print_status(philo, EAT_MSG);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal_time = get_time();
	philo->meals_already_eaten++;
	pthread_mutex_unlock(&philo->mutex);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
}