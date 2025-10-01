/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:42:10 by Mimoulapino       #+#    #+#             */
/*   Updated: 2025/10/01 05:41:15 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_single_fork(pthread_mutex_t *fork, t_philo *ph, int idx)
{
	while (1)
	{
		pthread_mutex_lock(&ph->data->data_mutex);
		if (!ph->data->is_running)
		{
			pthread_mutex_unlock(&ph->data->data_mutex);
			return (0);
		}
		pthread_mutex_unlock(&ph->data->data_mutex);
		pthread_mutex_lock(fork);
		if (ph->data->fork_taken[idx] == -1)
		{
			ph->data->fork_taken[idx] = 1;
			pthread_mutex_unlock(fork);
			print_status(ph, FORK_MSG);
			return (1);
		}
		pthread_mutex_unlock(fork);
		usleep(50);
	}
}
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