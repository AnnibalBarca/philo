/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:32:36 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/30 12:49:47 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		if (ft_strtol(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

static void	init_last_meal_times(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_phis)
	{
		pthread_mutex_lock(&data->philos[i].mutex);
		data->philos[i].last_meal_time = data->start_time;
		pthread_mutex_unlock(&data->philos[i].mutex);
		i++;
	}
}

static int	philo_startup(t_data *data, int k, int i)
{
	while (k < data->num_of_phis)
	{
		pthread_mutex_lock(&data->philos[k].mutex);
		k++;
	}
	while (i < data->num_of_phis)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (0);
		i++;
	}
	set_int(&data->data_mutex, &data->is_ready, 0);
	return (1);
}

static int	run_philo(t_data *data)
{
	int			i;
	int			k;
	pthread_t	monitor_thread;

	data->start_time = get_time();
	init_last_meal_times(data);
	k = 0;
	i = 0;
	if (!philo_startup(data, k, i))
		return (0);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
		return (0);
	while (k < data->num_of_phis)
	{
		pthread_mutex_unlock(&data->philos[k].mutex);
		k++;
	}
	i = 0;
	while (i < data->num_of_phis)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_args(ac, av))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (!data_init(&data, ac, av))
		return (1);
	if (!init_mutexes(&data))
		return (1);
	if (!init_philosophers(&data))
	{
		cleanup_mutexes_partial(&data, data.num_of_phis, 1, 1);
		return (1);
	}
	if (!run_philo(&data))
	{
		cleanup_all(&data);
		return (1);
	}
	cleanup_all(&data);
	return (0);
}
