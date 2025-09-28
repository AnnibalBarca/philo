/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:38:20 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/28 19:17:51 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->phi_id % 2 == 0)
	{
		take_single_fork(philo->right_fork, philo, philo->right_idx);
		take_single_fork(philo->left_fork, philo, philo->left_idx);
	}
	else
	{
		take_single_fork(philo->left_fork, philo, philo->left_idx);
		take_single_fork(philo->right_fork, philo, philo->right_idx);
	}
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo->data->fork_taken[philo->left_idx] = -1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	philo->data->fork_taken[philo->right_idx] = -1;
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	print_status(philo, EAT_MSG);
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->mutex);
	ft_usleep_ms(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->mutex);
	philo->meals_already_eaten++;
	pthread_mutex_unlock(&philo->mutex);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	ft_usleep_ms(philo->data->time_to_sleep, philo->data);
}

void	think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
}
