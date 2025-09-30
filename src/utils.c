/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:36:27 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/30 17:38:05 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->data_mutex);
	if (!philo->data->is_running && strcmp(msg, DEATH_MSG) != 0)
	{
		pthread_mutex_unlock(&philo->data->data_mutex);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	time = get_time() - philo->data->start_time;
	printf("%ld %d %s\n", time, philo->phi_id, msg);
	pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_usleep_ms(long ms, t_philo *philo)
{
	long	start;
	long	now;
	long	last_meal;

	start = get_time();
	while (1)
	{
		now = get_time();
		if (now - start >= ms)
			break ;
		pthread_mutex_lock(&philo->data->data_mutex);
		if (!philo->data->is_running)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		last_meal = get_long(&philo->mutex, &philo->last_meal_time);
		if (now - last_meal > philo->data->time_to_die)
			return (1);
		usleep(100);
	}
	return (0);
}

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

long int	ft_strtol(const char *str)
{
	long int	result;
	int			sign;
	size_t		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if ((result * 10 + str[i] - '0') / 10 != result)
		{
			if (sign == -1)
				return (LONG_MIN);
			return (LONG_MAX);
		}
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}
