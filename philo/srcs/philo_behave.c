/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behave.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:13:49 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 03:13:49 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_take_fork_left(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->fork[L]->lock);
	put_in_print_queue(philo, STATE_TAKE_FORK);
}

void	philo_take_fork_right(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->fork[R]->lock);
	put_in_print_queue(philo, STATE_TAKE_FORK);
}

void	philo_eat(t_philosopher *philo)
{
	write_mutexed_value(&philo->last_eat_time, \
											current_time(), sizeof(t_micsec));
	put_in_print_queue(philo, STATE_EATING);
	ph_usleep(philo->rules.time_eat);
	pthread_mutex_unlock(&philo->fork[L]->lock);
	pthread_mutex_unlock(&philo->fork[R]->lock);
}

void	philo_sleep(t_philosopher *philo)
{
	put_in_print_queue(philo, STATE_SLEEPING);
	ph_usleep(philo->rules.time_sleep);
}

void	philo_think(t_philosopher *philo)
{
	put_in_print_queue(philo, STATE_THINKING);
}
