/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:52:03 by almeekel          #+#    #+#             */
/*   Updated: 2025/09/28 18:52:19 by almeekel         ###   ########.fr       */
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

int	get_int(pthread_mutex_t *mtx, int *var)
{
	int	ret;

	pthread_mutex_lock(mtx);
	ret = *var;
	pthread_mutex_unlock(mtx);
	return (ret);
}
