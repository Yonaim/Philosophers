/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:10:39 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/13 20:07:06 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	free_fork_arr(t_fork *fork_arr, int fork_cnt)
{
	int	i;

	i = 0;
	while (i < fork_cnt)
	{
		pthread_mutex_destroy(&fork_arr[i].lock);
		i++;
	}
}

static void	free_philo_arr(t_philosopher *philo_arr, int philo_cnt)
{
	int	i;

	i = 0;
	while (i < philo_cnt)
	{
		pthread_mutex_destroy(&philo_arr[i].dining_status.lock);
		pthread_mutex_destroy(&philo_arr[i].last_eat_time.lock);
		pthread_mutex_destroy(&philo_arr[i].comm.simul_ended.lock);
		i++;
	}
}

static void	free_mutexs(t_simulation *simul)
{
	free_fork_arr(simul->fork_arr, simul->rules.philo_cnt);
	free_philo_arr(simul->philo_arr, simul->rules.philo_cnt);
	pthread_mutex_destroy(&simul->start);
	pthread_mutex_destroy(&simul->ended.lock);
	pthread_mutex_destroy(&simul->print_queue.lock);
}

void	finish_simulation(t_simulation *simul, pthread_t *thds)
{
	int	i;

	i = 0;
	while (i < simul->rules.philo_cnt)
	{
		pthread_join(thds[i], NULL);
		i++;
	}
	free_mutexs(simul);
	free(thds);
	printf(GREEN "Simulation ended successfully.\n" RESET);
}
