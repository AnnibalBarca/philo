/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 04:40:10 by Mimoulapino       #+#    #+#             */
/*   Updated: 2025/10/01 04:40:33 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mtx, bool *value, bool new_value)
{
	pthread_mutex_lock(mtx);
	*value = new_value;
	pthread_mutex_unlock(mtx);
}

void	set_int(pthread_mutex_t *mtx, int *value, int new_value)
{
	pthread_mutex_lock(mtx);
	*value = new_value;
	pthread_mutex_unlock(mtx);
}
void	set_long(pthread_mutex_t *mtx, long *value, long new_value)
{
	pthread_mutex_lock(mtx);
	*value = new_value;
	pthread_mutex_unlock(mtx);
}