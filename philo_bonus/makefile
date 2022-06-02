# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 18:11:26 by iomayr            #+#    #+#              #
#    Updated: 2022/05/31 14:10:04 by iomayr           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c bonus_utiles.c init_philo_bonus.c
OBJ = ${SRC:%.c=%.o}
NAME = philo_bonus

all : ${NAME} 

%.o:%.c philo_bonus.h
	@$(CC) -c $< -o $@

${NAME} : ${OBJ} philo_bonus.h
	@${CC} ${CFLAGS} ${OBJ} -o ${NAME}
	@echo "\033[1;32m##########COMPILED SUCCESSFULY##########\033[0m"

clean :
	@rm -rf *.o 

fclean : clean 
	@rm -rf ${NAME}
	@echo "\033[1;32m##########CLEANED SUCCESSFULY##########\033[0m"

re : fclean all