/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:18:36 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/27 16:49:39 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_philo_dead(t_data *data, int i)
{
	long long current_time;
	long long last_meal;

	current_time = get_time();
	pthread_mutex_lock(&data->philos[i].mutex);
	last_meal = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->philos[i].mutex);
	if (current_time - last_meal > data->time_to_die)
	{
		print_status(&data->philos[i], DEATH_MSG);
		pthread_mutex_lock(&data->data_mutex);
		data->is_running = 0;
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	return (0);
}

static int	have_philos_eaten_all(t_data *data, int all_have_eaten)
{
	pthread_mutex_lock(&data->data_mutex);
	if (data->num_of_meals > 0 && all_have_eaten)
	{
		data->is_running = 0;
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}

static int	check_phis(t_data *data, int all_have_eaten)
{
	int	i;
	int	num_philosophers;

	i = 0;
	pthread_mutex_lock(&data->data_mutex);
	num_philosophers = data->num_of_phis;
	pthread_mutex_unlock(&data->data_mutex);
	all_have_eaten = 1;
	while (i < num_philosophers)
	{
		pthread_mutex_lock(&data->philos[i].mutex);
		if (data->philos[i].meals_already_eaten < data->num_of_meals)
			all_have_eaten = 0;
		pthread_mutex_unlock(&data->philos[i].mutex);
		i++;
	}
	i = 0;
	while (i < num_philosophers)
	{
		if (is_philo_dead(data, i))
			return (-1);
		i++;
	}
	return (all_have_eaten);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		all_have_eaten;

	all_have_eaten = 0;
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		all_have_eaten = check_phis(data, all_have_eaten);
		if (all_have_eaten == -1)
			return (NULL);
		if (have_philos_eaten_all(data, all_have_eaten))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
