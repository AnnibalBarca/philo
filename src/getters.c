/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:52:03 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/01 04:40:27 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(pthread_mutex_t *mtx, bool *var)
{
	bool	ret;

	pthread_mutex_lock(mtx);
	ret = *var;
	pthread_mutex_unlock(mtx);
	return (ret);
}

int	get_int(pthread_mutex_t *mtx, int *var)
{
	int	ret;

	pthread_mutex_lock(mtx);
	ret = *var;
	pthread_mutex_unlock(mtx);
	return (ret);
}

long	get_long(pthread_mutex_t *mtx, long *var)
{
	long	ret;

	pthread_mutex_lock(mtx);
	ret = *var;
	pthread_mutex_unlock(mtx);
	return (ret);
}
