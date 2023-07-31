# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 12:01:22 by jperinch          #+#    #+#              #
#    Updated: 2023/07/31 12:45:39 by jperinch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC = 	inint.c  main.c    mutex_events.c  threadjob.c todo.c ft_atoi.c
OBJ	= $(SRC:.c=.o)

CFLAGS = -pthread  -g3   -Wall -Wextra -Werror
CC = gcc


all:  $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf *.o 

fclean:
	rm -f $(NAME) *.o 

re:     fclean all