/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:32:36 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/23 17:35:44 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
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
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data			data;

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