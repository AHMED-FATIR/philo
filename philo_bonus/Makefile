# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afatir <afatir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 14:35:22 by afatir            #+#    #+#              #
#    Updated: 2023/05/07 18:14:12 by afatir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
CFLAGS	= -Wall -Werror -Wextra 
-fsanitize=thread
-fsanitize=address
CC		= cc
MOBJS	= ${SRCS:%.c=%.o}
SRCS	= philo_bonus.c parsing_bonus.c routine_bonus.c simulation_bonus.c simulation2_bonus.c

all : $(NAME)

$(NAME) : $(MOBJS)
	@$(CC) $(CFLAGS) $(LIB_FT_A) $(MOBJS) -o $(NAME)
	@make clean

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	@rm -f $(MOBJS) 

fclean:	clean
	@rm -f $(NAME)

re:	fclean all