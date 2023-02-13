/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 05:27:23 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 03:16:05 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	start_simulation(t_simulation *simul, pthread_t **thds)
{
	int	i;

	*thds = malloc(sizeof(pthread_t) * simul->rules.philo_cnt);
	pthread_mutex_lock(&simul->start);
	i = 0;
	while (i < simul->rules.philo_cnt)
	{
		if (pthread_create(&(*thds)[i], NULL, \
							philo_routine, &simul->philo_arr[i]))
			return (FAILURE);
		i++;
	}
	simul->start_time = current_time();
	pthread_mutex_unlock(&simul->start);
	usleep(simul->rules.time_die * 0.7);
	return (SUCCESS);
}
