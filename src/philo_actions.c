/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:38:20 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/26 09:44:43 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->phi_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_MSG);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_MSG);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_MSG);
		pthread_mutex_lock(philo->right_fork);
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
	philo->last_meal_time = get_time();
	usleep(philo->data->time_to_eat * 1000);
	philo->meals_already_eaten++;
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