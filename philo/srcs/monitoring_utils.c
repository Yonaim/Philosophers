/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:57:08 by yona              #+#    #+#             */
/*   Updated: 2023/02/12 03:13:24 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_died(t_philosopher *philo)
{
	const t_micsec	last_eat_time = \
					read_mutexed_value(&philo->last_eat_time, sizeof(t_micsec));
	const t_micsec	since_last_eat = current_time() - last_eat_time;

	return (since_last_eat > philo->rules.time_die);
}

int	is_there_a_died_philo(t_simulation *simul, int *died_philo_id)
{
	int	i;

	i = 0;
	while (i < simul->rules.philo_cnt)
	{
		if (is_died(&simul->philo_arr[i]))
		{
			*died_philo_id = simul->philo_arr[i].id;
			return (true);
		}
		i++;
	}
	return (false);
}

int	is_dining_all_complete(t_simulation *simul)
{
	int	i;

	i = 0;
	while (i < simul->rules.philo_cnt)
	{
		if (read_mutexed_value(&simul->philo_arr[i].dining_status, \
													sizeof(int)) == INCOMPLETE)
		{
			return (false);
		}
		i++;
	}
	return (true);
}
