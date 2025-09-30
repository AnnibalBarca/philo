/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:02:47 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/30 14:50:36 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cleanup_mutexes_partial(t_data *data, int forks_initialized,
		int print_initialized, int data_initialized)
{
	int	i;

	i = 0;
	while (i < forks_initialized)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (print_initialized)
		pthread_mutex_destroy(&data->print_mutex);
	if (data_initialized)
		pthread_mutex_destroy(&data->data_mutex);
	free(data->forks);
	return (0);
}

void	cleanup_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_phis)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	free(data->forks);
	free(data->fork_taken);
	free(data->philos);
}
