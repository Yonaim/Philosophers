/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:15:37 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 06:08:29 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	put_in_print_queue(t_philosopher *philo, int state)
{
	const t_print	in = {
		philo->id, state, elapsed_time(*philo->comm.start_time) / 1000
	};

	if (enqueue(philo->comm.print_queue, in) == FAILURE)
	{
		printf(YELLO "Print queue is full. Increase QUEUE_SIZE\n" RESET);
	}
}

void	print_state_log(t_print_queue *queue)
{
	t_print				print;
	static const char	*state_strs[] = {
	[STATE_TAKE_FORK] = STATE_STR_TAKE_FORK,
	[STATE_DOWN_FORK] = STATE_STR_DOWN_FORK,
	[STATE_EATING] = STATE_STR_EATING,
	[STATE_SLEEPING] = STATE_STR_SLEEPING,
	[STATE_THINKING] = STATE_STR_THINKING,
	[STATE_DIED] = STATE_STR_DIED
	};

	if (dequeue(queue, &print) == SUCCESS)
	{
		printf(state_strs[print.state], print.time_stamp, print.id);
	}
}
