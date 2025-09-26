/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:32:36 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/26 09:46:38 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(int ac, char **av)
{
	int i;
	int j;

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
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int run_philo(t_data *data)
{
	int i;
	pthread_t monitor_thread;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_of_phis)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->num_of_phis)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
		return (0);
	i = 0;
	while (i < data->num_of_phis)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
}

int main(int ac, char **av)
{
	t_data data;

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
