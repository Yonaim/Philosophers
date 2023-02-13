/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:13:53 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 05:10:20 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_simulation_ended(t_philosopher *philo)
{
	return (read_mutexed_value(&philo->comm.simul_ended, sizeof(int)));
}

static int	do_finite_dining(t_philosopher *philo)
{
	int	eat_cnt;

	eat_cnt = 0;
	while (is_simulation_ended(philo) == false)
	{
		philo_take_fork_left(philo);
		philo_take_fork_right(philo);
		philo_eat(philo);
		if (++eat_cnt == philo->rules.must_eat_cnt)
			return (COMPLETE);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (INCOMPLETE);
}

static void	do_infinite_dining(t_philosopher *philo)
{
	while (is_simulation_ended(philo) == false)
	{
		philo_take_fork_left(philo);
		philo_take_fork_right(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return ;
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(philo->comm.simul_start);
	pthread_mutex_unlock(philo->comm.simul_start);
	write_mutexed_value(&philo->last_eat_time, \
									*philo->comm.start_time, sizeof(t_micsec));
	if (philo->rules.philo_cnt > 1 && philo->id % 2 == 1)
		ph_usleep((philo->rules.time_eat / 2));
	if (philo->rules.must_eat_cnt == INFINITE_DINING)
	{
		do_infinite_dining(philo);
	}
	else
	{
		if (do_finite_dining(philo) == COMPLETE)
			write_mutexed_value(&philo->dining_status, COMPLETE, sizeof(int));
	}
	return (NULL);
}
