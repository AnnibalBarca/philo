/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:38:20 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/30 16:08:49 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	int				first_idx;
	int				second_idx;

	if (philo->phi_id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
		first_idx = philo->right_idx;
		second_idx = philo->left_idx;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
		first_idx = philo->left_idx;
		second_idx = philo->right_idx;
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (!philo->data->is_running)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		if (philo->phi_id % 2 == 0)
		{
			take_single_fork(second, philo, second_idx);
			take_single_fork(first, philo, first_idx);
		}
		else
		{
			take_single_fork(first, philo, first_idx);
			take_single_fork(second, philo, second_idx);
		}
		return ;
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
	set_long(&philo->mutex, &philo->last_meal_time, get_time());
	print_status(philo, EAT_MSG);
	ft_usleep_ms(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->mutex);
	philo->meals_already_eaten++;
	pthread_mutex_unlock(&philo->mutex);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	ft_usleep_ms(philo->data->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
}
