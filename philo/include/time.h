/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 04:57:07 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/02/12 04:58:29 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

/*-------------- STANDARD HEADERS ---------------*/

# include <stdint.h>

/*----------------- TYPE DEFINE ------------------*/

typedef uint64_t	t_micsec;
typedef uint64_t	t_milsec;

/*-------------- FUNCTION PROTOTYPES -------------*/

t_micsec	current_time(void);
t_micsec	elapsed_time(t_micsec start_time);

#endif