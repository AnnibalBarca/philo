/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:38:20 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/01 04:45:34 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	set_long(&philo->mutex, &philo->last_meal_time, get_time());
	print_status(philo, EAT_MSG);
	ft_usleep_ms(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->mutex);
	philo->meals_already_eaten++;
	pthread_mutex_unlock(&philo->mutex);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	ft_usleep_ms(philo->data->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
}
