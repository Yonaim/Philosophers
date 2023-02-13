# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 02:56:10 by yeonhkim          #+#    #+#              #
#    Updated: 2023/02/12 06:03:54 by yeonhkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL	= all

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -fsanitize=address
# CFLAGS			= -Wall -Wextra -Werror
CPPFLAGS		= -I./include

# *********************************** PHILO ********************************** #

PHILO			= philo
PHILO_SRCS		=	\
					create_threads.c \
					end_simulation.c \
					init_simulation.c \
					main.c \
					monitoring.c \
					monitoring_utils.c \
					parse.c \
					ph_usleep.c \
					philo_behave.c \
					philo_routine.c \
					print.c \
					queue_operations.c \
					rw_mutexed.c \
					start_simulation.c \
					time.c

$(PHILO): $(addprefix ./srcs/, $(PHILO_SRCS:.c=$(SUFFIX).o))
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

# ********************************* MAKE RULES ******************************* #
# **************************************************************************** #

all:
	make $(PHILO)

clean:
	rm -f $(addprefix ./srcs/, $(PHILO_SRCS:.c=.o))

fclean:
	rm -f $(addprefix ./srcs/, $(PHILO_SRCS:.c=.o))
	rm -f $(PHILO)

re: 
	make fclean
	make all

.PHONY: all clean fclean re bonus