# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afatir <afatir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 14:35:22 by afatir            #+#    #+#              #
#    Updated: 2023/03/08 13:34:15 by afatir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
# BNAME	= checker

CFLAGS	= -Wall -Werror -Wextra
CC		= cc

MOBJS	= ${SRCS:%.c=%.o}
# BOBJS	= ${SRCS_B:%.c=%.o}

SRCS	= main.c

# SRCS_B	=

all : $(NAME)

$(NAME) : $(MOBJS)
	@$(CC) $(CFLAGS) $(LIB_FT_A) $(MOBJS) -o $(NAME)

# bonus: $(BNAME)

# $(BNAME): $(BOBJS)
# 	@$(CC) $(CFLAGS) $(BOBJS) -o $(BNAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	@rm -f $(MOBJS) 

fclean: clean
	@rm -f $(NAME)

re: 		fclean all