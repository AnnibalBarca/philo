/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:02:47 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/01 05:41:45 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_until_index(int forks_initialized, pthread_mutex_t *__mutex)
{
	int	i;

	i = 0;
	while (i < forks_initialized)
	{
		pthread_mutex_destroy(&__mutex[i]);
		i++;
	}
}

int	cleanup_mutexes_partial(t_data *data, int forks_initialized,
		int print_initialized, int data_initialized)
{
	cleanup_until_index(forks_initialized, data->forks);
	if (print_initialized)
		pthread_mutex_destroy(&data->print_mutex);
	if (data_initialized)
		pthread_mutex_destroy(&data->data_mutex);
	if (data->forks)
		free(data->forks);
	if (data->fork_taken)
		free(data->fork_taken);
	if (data->philos)
		free(data->philos);
	return (0);
}

int	cleanup_init_philos_partial(t_data *data, int philos_initialized)
{
	int	i;

	i = 0;
	while (i < philos_initialized)
	{
		pthread_mutex_destroy(&data->philos[i].mutex);
		pthread_mutex_destroy(&data->philos[i].start_mutex);
		i++;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
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
