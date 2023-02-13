/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:10:23 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 03:40:21 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_mutexed_value(t_mutexed_value *mutexed, int64_t initial_value)
{
	if (pthread_mutex_init(&mutexed->lock, NULL) == -1)
		return (FAILURE);
	write_mutexed_value(mutexed, initial_value, sizeof(int64_t));
	return (SUCCESS);
}

static int	init_philo(t_philosopher *philo, t_simulation *simul, int nth)
{
	philo->id = nth + 1;
	philo->rules = simul->rules;
	philo->comm.simul_start = &simul->start;
	philo->comm.start_time = &simul->start_time;
	philo->comm.print_queue = &simul->print_queue;
	if (init_mutexed_value(&philo->comm.simul_ended, false) == FAILURE \
		|| init_mutexed_value(&philo->dining_status, INCOMPLETE) == FAILURE \
		|| init_mutexed_value(&philo->last_eat_time, 0) == FAILURE)
		return (FAILURE);
	if (nth == 0)
		philo->fork[L] = &simul->fork_arr[simul->rules.philo_cnt - 1];
	else
		philo->fork[L] = &simul->fork_arr[nth - 1];
	philo->fork[R] = &simul->fork_arr[nth];
	return (SUCCESS);
}

static int	init_philo_arr(t_philosopher **philo_arr, t_simulation *simul)
{
	int	i;

	*philo_arr = malloc(sizeof(t_philosopher) * simul->rules.philo_cnt);
	if (!(*philo_arr))
		return (FAILURE);
	i = 0;
	while (i < simul->rules.philo_cnt)
	{
		if (init_philo(&(*philo_arr)[i], simul, i) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	init_fork_arr(t_fork **fork_arr, t_simulation *simul)
{
	int	i;

	*fork_arr = malloc(sizeof(t_fork) * simul->rules.philo_cnt);
	if (!(*fork_arr))
		return (FAILURE);
	i = 0;
	while (i < simul->rules.philo_cnt)
	{
		if (pthread_mutex_init(&(*fork_arr)[i].lock, NULL) != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	init_simulation(t_simulation *simul)
{
	if (init_fork_arr(&simul->fork_arr, simul) == FAILURE \
			|| init_philo_arr(&simul->philo_arr, simul) == FAILURE \
			|| init_mutexed_value(&simul->ended, true) == FAILURE \
			|| pthread_mutex_init(&simul->start, NULL) \
			|| pthread_mutex_init(&simul->print_queue.lock, NULL))
		return (FAILURE);
	simul->print_queue.front = 0;
	simul->print_queue.rear = 0;
	return (SUCCESS);
}
