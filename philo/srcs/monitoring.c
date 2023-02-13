/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:57:10 by yona              #+#    #+#             */
/*   Updated: 2023/02/13 19:26:47 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	announce_end_of_simulation(t_simulation *simul)
{
	int	i;

	i = 0;
	while (i < simul->rules.philo_cnt)
	{
		write_mutexed_value(&simul->philo_arr[i].comm.simul_ended, \
							true, sizeof(int));
		i++;
	}
}

static void	watch_infinite_dining_until_end(t_simulation *simul)
{
	int	died_philo_id;

	while (1)
	{
		if (is_there_a_died_philo(simul, &died_philo_id))
		{
			printf(STATE_STR_DIED, \
					elapsed_time(simul->start_time) / 1000, died_philo_id);
			printf(MAGENTA "A philosopher died during dining.\n" RESET);
			break ;
		}
		print_state_log(&simul->print_queue);
	}
}

static void	watch_finite_dining_until_end(t_simulation *simul)
{
	int	died_philo_id;

	while (1)
	{
		if (is_dining_all_complete(simul))
		{
			printf(CYAN "All the philosopher's completed dining.\n" RESET);
			break ;
		}
		if (is_there_a_died_philo(simul, &died_philo_id))
		{
			printf(STATE_STR_DIED, \
					elapsed_time(simul->start_time) / 1000, died_philo_id);
			printf(MAGENTA "A philosopher died during dining.\n" RESET);
			break ;
		}
		print_state_log(&simul->print_queue);
	}
}

static void	watch_inevitable_sole_died(t_simulation *simul)
{
	while (elapsed_time(simul->start_time) < simul->rules.time_die)
		print_state_log(&simul->print_queue);
	printf(STATE_STR_DIED, elapsed_time(simul->start_time) / 1000, 1);
}

int	monitoring(t_simulation *simul)
{
	if (simul->rules.philo_cnt == 1)
	{
		watch_inevitable_sole_died(simul);
		return (FAILURE);
	}
	else
	{
		if (simul->rules.must_eat_cnt == INFINITE_DINING)
			watch_infinite_dining_until_end(simul);
		else
			watch_finite_dining_until_end(simul);
		announce_end_of_simulation(simul);
	}
	return (SUCCESS);
}
