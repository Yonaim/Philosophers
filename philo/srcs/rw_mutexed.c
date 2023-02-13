/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_mutexed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:15:58 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 03:15:58 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int64_t	read_mutexed_value(t_mutexed_value *mutexed, size_t value_size)
{
	int64_t	value;

	pthread_mutex_lock(&mutexed->lock);
	if (value_size == sizeof(int32_t))
		value = mutexed->v.int32;
	else
		value = mutexed->v.int64;
	pthread_mutex_unlock(&mutexed->lock);
	return (value);
}

void	write_mutexed_value(t_mutexed_value *mutexed, \
							int64_t new_value, size_t value_size)
{
	pthread_mutex_lock(&mutexed->lock);
	if (value_size == sizeof(int32_t))
		mutexed->v.int32 = new_value;
	else
		mutexed->v.int64 = new_value;
	pthread_mutex_unlock(&mutexed->lock);
}
