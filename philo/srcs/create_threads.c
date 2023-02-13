/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:51:57 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 05:15:50 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_philo_threads(pthread_t *thds, \
									t_philosopher *philo_arr, int philo_cnt)
{
	int	i;

	i = 0;
	while (i < philo_cnt)
	{
		if (pthread_create(&thds[i], NULL, philo_routine, &philo_arr[i]))
		{
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
