# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/07 11:53:43 by ibra              #+#    #+#              #
#    Updated: 2022/05/27 18:20:49 by iomayr           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c utiles_philo.c init_philo.c
OBJ = ${SRC:%.c=%.o}
NAME = philo 

all : ${NAME} 

%.o:%.c philo.h
	@$(CC) ${CFLAGS} -c $< -o $@

${NAME} : ${OBJ} philo.h
	@${CC} ${CFLAGS} ${OBJ} -o ${NAME}
	@echo "\033[1;32m##########COMPILED SUCCESSFULY##########\033[0m"

clean :
	@rm -rf *.o 

fclean : clean 
	@rm -rf ${NAME}
	@echo "\033[1;32m##########CLEANED SUCCESSFULY##########\033[0m"

re : fclean all