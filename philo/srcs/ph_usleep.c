/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 23:14:23 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 02:51:49 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ph_usleep(t_micsec micsec)
{
	const t_micsec	start_time = current_time();
	const t_micsec	end_time = start_time + micsec;

	usleep(micsec * 0.9);
	while (1)
	{
		usleep(1);
		if (current_time() >= end_time)
			return ;
	}
}
