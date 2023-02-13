/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 04:46:02 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/13 20:09:18 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

/*-------------- STANDARD HEADERS ---------------*/

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

/*------------- USER DEFINED HEADERS ------------*/

# include "color.h"
# include "time.h"
# include "queue.h"

/*----------- DEFINE MACRO CONSTANTS ------------*/

# define SUCCESS				 0
# define FAILURE 				-1

# define STATE_STR_TAKE_FORK	"%lld %d has taken a fork\n"
# define STATE_STR_DOWN_FORK	"%lld %d has put down a fork\n"
# define STATE_STR_EATING		"%lld %d is eating\n"
# define STATE_STR_SLEEPING		"%lld %d is sleeping\n"
# define STATE_STR_THINKING		"%lld %d is thinking\n"
# define STATE_STR_DIED			"%lld %d died\n"

enum	e_error_code {
	ERROR_NONE,
	ERROR_INVALID_ARGUMENT,
	ERROR_INIT_FAILED,
	ERROR_START_FAILED,
	ERROR_DURING_SIMULATION,
	ERROR_QUEUE_FULLED
};

enum	e_argument_of_rules {
	INVALID_ARGUMENT = -1,
	INFINITE_DINING = -2
};

enum	e_fork_type {
	L,
	R
};

enum	e_philo_state {
	STATE_TAKE_FORK,
	STATE_DOWN_FORK,
	STATE_EATING,
	STATE_SLEEPING,
	STATE_THINKING,
	STATE_DIED
};

enum	e_dining_status {
	COMPLETE,
	INCOMPLETE
};

/*-------------- UNION DECLARATIONS --------------*/

typedef union u_value {
	int32_t					int32;
	int64_t					int64;
}	t_value;

/*------------- STRUCT DECLARATIONS --------------*/

typedef struct s_fork {
	pthread_mutex_t			lock;
}	t_fork;

typedef struct s_rules {
	int						philo_cnt;
	t_micsec				time_die;
	t_micsec				time_eat;
	t_micsec				time_sleep;
	int						must_eat_cnt;
}	t_rules;

typedef struct s_mutexed_value {
	union u_value			v;
	pthread_mutex_t			lock;
}	t_mutexed_value;

typedef struct s_in_common {
	t_micsec				*start_time;
	pthread_mutex_t			*simul_start;
	struct s_mutexed_value	simul_ended;
	t_print_queue			*print_queue;
}	t_in_common;

typedef struct s_philosopher {
	int						id;
	struct s_fork			*fork[2];
	struct s_mutexed_value	dining_status;
	struct s_mutexed_value	last_eat_time;
	struct s_in_common		comm;
	struct s_rules			rules;
}	t_philosopher;

typedef struct s_simulation {
	pthread_mutex_t			start;
	struct s_mutexed_value	ended;
	struct s_rules			rules;
	struct s_fork			*fork_arr;
	struct s_philosopher	*philo_arr;
	t_micsec				start_time;
	t_print_queue			print_queue;
}	t_simulation;

/*-------------- FUNCTION PROTOTYPES -------------*/

/* prepare simulation */
int			parse_rules(t_rules *rules, char *argv[]);
int			init_simulation(t_simulation *simul);

/* start simulation */
void		*philo_routine(void *arg);
int			create_philo_threads(pthread_t *thds, \
								t_philosopher *philo_arr, int philo_cnt);

/* monitor simulation */
int			monitoring(t_simulation *simul);

/* end simulation */
void		abort_simulation(t_simulation *simul, pthread_t *thds);
void		finish_simulation(t_simulation *simul, pthread_t *thds);

/* behaviors of philosopher */
void		philo_take_fork_left(t_philosopher *philo);
void		philo_take_fork_right(t_philosopher *philo);
void		philo_eat(t_philosopher *philo);
void		philo_sleep(t_philosopher *philo);
void		philo_think(t_philosopher *philo);

/* read & write mutexed value */
int64_t		read_mutexed_value(t_mutexed_value *mutexed, size_t value_size);
void		write_mutexed_value(t_mutexed_value *mutexed, \
										int64_t new_value, size_t value_size);

/* print utils */
void		put_in_print_queue(t_philosopher *philo, int state);
void		print_state_log(t_print_queue *queue);

/* monitoring utils */
int			is_there_a_died_philo(t_simulation *simul, int *died_philo_id);
int			is_dining_all_complete(t_simulation *simul);

/* usleep for multi-threading environment */
void		ph_usleep(t_micsec micsec);

#endif