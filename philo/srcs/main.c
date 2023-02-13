/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:13:16 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 05:30:39 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	prepare_simulation(char *argv[], t_simulation *simul, int *err)
{
	if (parse_rules(&simul->rules, argv) == FAILURE)
	{
		*err = ERROR_INVALID_ARGUMENT;
		return ;
	}
	if (init_simulation(simul) == FAILURE)
	{
		*err = ERROR_INIT_FAILED;
		return ;
	}
}

static void	start_simulation(t_simulation *simul, pthread_t **thds, int *err)
{
	if (*err)
		return ;
	*thds = malloc(sizeof(pthread_t) * simul->rules.philo_cnt);
	pthread_mutex_lock(&simul->start);
	if (create_philo_threads(*thds, simul->philo_arr, \
										simul->rules.philo_cnt) == FAILURE)
	{
		*err = ERROR_START_FAILED;
		return ;
	}
	simul->start_time = current_time();
	pthread_mutex_unlock(&simul->start);
	ph_usleep(simul->rules.time_die * 0.7);
}

static void	monitor_simulation(t_simulation *simul, int *err)
{
	if (*err)
		return ;
	if (monitoring(simul) == FAILURE)
	{
		*err = ERROR_DURING_SIMULATION;
		return ;
	}
}

static void	print_errmsg(int err)
{
	printf(RED "Error: ");
	if (err == ERROR_INVALID_ARGUMENT)
		printf("Invalid argument");
	else if (err == ERROR_INIT_FAILED)
		printf("init simulation failed");
	else if (err == ERROR_START_FAILED)
		printf("start simulation failed");
	else if (err == ERROR_DURING_SIMULATION)
		printf("unexpected error occured during simulation");
	printf("\n" RESET);
}

int	main(int argc, char *argv[])
{
	t_simulation	simul;
	pthread_t		*thds;
	int				err;

	if (argc != 5 && argc != 6)
	{
		printf("\nUsage: <philo_cnt> <time_die> \
<time_eat> <time_sleep> [must_eat_cnt]\n\n");
		return (1);
	}
	err = 0;
	prepare_simulation(argv, &simul, &err);
	start_simulation(&simul, &thds, &err);
	monitor_simulation(&simul, &err);
	if (err)
	{
		print_errmsg(err);
		end_aborted_simulation(&simul, thds);
		return (1);
	}
	else
	{
		end_finished_simulation(&simul, thds);
		return (0);
	}
}
