# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lquehec <lquehec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 19:51:48 by lquehec           #+#    #+#              #
#    Updated: 2024/02/08 17:47:27 by lquehec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
END=\x1b[0m
BOLD=\x1b[1m
UNDER=\x1b[4m
REV=\x1b[7m
GREY=\x1b[30m
RED=\x1b[31m
GREEN=\x1b[32m
YELLOW=\x1b[33m
BLUE=\x1b[34m
PURPLE=\x1b[35m
CYAN=\x1b[36m
WHITE=\x1b[37m

OS 			:= $(shell uname)
VPATH		= srcs srcs/activities srcs/utils
HEADER_DIR	= includes
OBJ_DIR 	= .obj

SRCS 		= main.c \
				exit.c \
				init.c \
				philo.c \
				utils.c \
				libft.c \
				monitoring.c \
				go_eat.c \
				go_sleep.c \
				go_think.c

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -pthread -fsanitize=thread -g3

NAME		= philo

all: 		$(NAME)

$(NAME):	${OBJ_DIR} $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "\n${GREEN}> $(NAME) was successfuly compiled 🎉${END}"

$(OBJ_DIR):
			@mkdir -p ${OBJ_DIR}

$(OBJ_DIR)/%.o: %.c
			@/bin/echo -n .
			@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
			@$(RM) $(OBJ_DIR)
			@echo "${YELLOW}> All objects files of $(NAME) have been deleted ❌${END}"

fclean:		clean
			@$(RM) $(NAME)
			@echo "${YELLOW}> Cleaning of $(NAME) has been done ❌${END}"

re:			fclean all

.PHONY: all clean fclean re