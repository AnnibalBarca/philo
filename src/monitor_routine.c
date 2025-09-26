/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:18:36 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/26 11:14:39 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_philo_dead(t_data *data, int i)
{
	if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
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
	if (data->num_of_meals > 0 && all_have_eaten)
	{
		pthread_mutex_lock(&data->data_mutex);
		data->is_running = 0;
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	int		all_have_eaten;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		all_have_eaten = 1;
		while (i < data->num_of_phis)
		{
			if (is_philo_dead(data, i))
				return (NULL);
			if (data->num_of_meals > 0
				&& data->philos[i].meals_already_eaten < data->num_of_meals)
				all_have_eaten = 0;
			i++;
		}
		if (have_philos_eaten_all(data, all_have_eaten))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
