/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:36:25 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/19 14:18:05 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	data_init(t_data *data, int ac, char **av)
{
	data->num_of_phis = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_of_meals = ft_atoi(av[5]);
	else
		data->num_of_meals = -1;
	data->is_running = 1;
	return (1);
}

int	init_mutexes(t_data *data)
{
	int i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_phis);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->num_of_phis)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (cleanup_mutexes_partial(data, i, 0, 0));
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (cleanup_mutexes_partial(data, data->num_of_phis, 0, 0));
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (cleanup_mutexes_partial(data, data->num_of_phis, 1, 0));
	return (1);
}
static void	assign_forks(t_philo *philo, t_data *data, int i)
{
	if (i == 0)
	{
		philo->left_fork = &data->forks[data->num_of_phis - 1];
		philo->right_fork = &data->forks[i];
	}
	else
	{
		philo->left_fork = &data->forks[i - 1];
		philo->right_fork = &data->forks[i];
	}
}
int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_of_phis);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->num_of_phis)
	{
		data->philos[i].phi_id = i + 1;
		data->philos[i].state = THINKING;
		data->philos[i].meals_already_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		assign_forks(&data->philos[i], data, i);
		i++;
	}
	return (1);
}
