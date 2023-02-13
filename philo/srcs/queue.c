/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:15:43 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/13 19:39:43 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_empty(t_print_queue *queue)
{
	return (queue->rear == queue->front);
}

static int	is_fulled(t_print_queue *queue)
{
	return (((queue->rear + 1) % QUEUE_SIZE) == queue->front);
}

int	dequeue(t_print_queue *queue, t_print *out)
{
	pthread_mutex_lock(&queue->lock);
	if (is_empty(queue))
	{
		pthread_mutex_unlock(&queue->lock);
		return (FAILURE);
	}
	queue->front = (queue->front + 1) % QUEUE_SIZE;
	*out = queue->data[queue->front];
	pthread_mutex_unlock(&queue->lock);
	return (SUCCESS);
}

int	enqueue(t_print_queue *queue, t_print put)
{
	pthread_mutex_lock(&queue->lock);
	if (is_fulled(queue))
	{
		pthread_mutex_unlock(&queue->lock);
		return (FAILURE);
	}
	queue->rear = (queue->rear + 1) % QUEUE_SIZE;
	queue->data[queue->rear] = put;
	pthread_mutex_unlock(&queue->lock);
	return (SUCCESS);
}
