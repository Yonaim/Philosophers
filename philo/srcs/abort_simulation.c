/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abort_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:05:53 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/13 20:07:27 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	abort_simulation(t_simulation *simul, pthread_t *thds)
{
	int	i;

	i = 0;
	while (i < simul->rules.philo_cnt)
	{
		pthread_detach(thds[i]);
		i++;
	}
	printf(RED "Simulation aborted due to an error.\n" RESET);
}
