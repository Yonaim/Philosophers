/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 03:13:37 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 05:45:41 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	is_valid_rules(struct s_rules *rules)
{
	if (rules->philo_cnt != INVALID_ARGUMENT \
		&& rules->philo_cnt > 0 \
		&& (int)rules->time_die != INVALID_ARGUMENT \
		&& (int)rules->time_eat != INVALID_ARGUMENT \
		&& (int)rules->time_sleep != INVALID_ARGUMENT \
		&& (int)rules->must_eat_cnt != INVALID_ARGUMENT)
		return (true);
	else
		return (false);
}

static int	phil_atoi(const char *str)
{
	int	n;

	while (*str == '\t' || *str == '\n' || *str == '\v' \
						|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (INVALID_ARGUMENT);
		str++;
	}
	if (!('0' <= *str && *str <= '9'))
		return (INVALID_ARGUMENT);
	n = 0;
	while ('0' <= *str && *str <= '9')
	{
		if (n >= 214748365 || (n == 214748364 && *str > '7'))
			return (INVALID_ARGUMENT);
		n = (n * 10) + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (INVALID_ARGUMENT);
	return (n);
}

int	parse_rules(t_rules *rules, char *argv[])
{
	{
		rules->philo_cnt = phil_atoi(argv[1]);
		rules->time_die = phil_atoi(argv[2]) * 1000;
		rules->time_eat = phil_atoi(argv[3]) * 1000;
		rules->time_sleep = phil_atoi(argv[4]) * 1000;
		if (argv[5])
			rules->must_eat_cnt = phil_atoi(argv[5]);
		else
			rules->must_eat_cnt = INFINITE_DINING;
	}
	if (is_valid_rules(rules))
		return (SUCCESS);
	else
		return (FAILURE);
}
