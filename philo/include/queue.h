/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 04:42:04 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 06:09:03 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

/*------------- USER DEFINED HEADERS ------------*/

# include "time.h"

/*----------- DEFINE MACRO CONSTANTS ------------*/

# ifndef QUEUE_SIZE
#  define QUEUE_SIZE		4096
# endif

/*------------- STRUCT DECLARATIONS --------------*/

typedef struct s_print {
	int						id;
	int						state;
	t_milsec				time_stamp;
}	t_print;

typedef struct s_print_queue {
	t_print					data[QUEUE_SIZE];
	int						front;
	int						rear;
	size_t					size;
	pthread_mutex_t			lock;
}	t_print_queue;

/*-------------- FUNCTION PROTOTYPES -------------*/

int		enqueue(t_print_queue *queue, t_print put);
int		dequeue(t_print_queue *queue, t_print *out);

#endif
