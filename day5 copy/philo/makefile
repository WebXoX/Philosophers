# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 12:01:22 by jperinch          #+#    #+#              #
#    Updated: 2023/07/26 13:28:22 by jperinch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC = 	inint.c  main.c    mutex_events.c  threadjob.c todo.c
OBJ	= $(SRC:.c=.o)

CFLAGS = -pthread  -g3 -Wall -Wextra -Werror # -fsanitize=thread
CC = gcc


all:  $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf *.o 

fclean:
	rm -f $(NAME) *.o 

re:     fclean all