# COLORS
END=$'\x1b[0m
BOLD=$'\x1b[1m
UNDER=$'\x1b[4m
REV=$'\x1b[7m
GREY=$'\x1b[30m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m
BLUE=$'\x1b[34m
PURPLE=$'\x1b[35m
CYAN=$'\x1b[36m
WHITE=$'\x1b[37m

OS 			:= $(shell uname)
VPATH		= srcs srcs/activities srcs/threads
HEADER_DIR	= ./includes/
OBJ_DIR 	= .obj

SRCS 		= main.c \
				exit.c \
				init.c \
				philo.c \
				utils.c \
				thread.c \
				monitoring.c \
				go_eat.c \
				go_sleep.c \
				go_think.c

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -pthread -fsanitize=thread -g3

# LIBFT
LIBFT_DIR	= ./libft
MAKE_LIBFT	= make -s -C $(LIBFT_DIR)
LIBFT_PATH	= $(LIBFT_DIR)/libft.a

NAME		= philo

all: 		$(NAME)

$(NAME):	${OBJ_DIR} $(OBJS) libft
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH) -o $(NAME)
			@echo "\n${GREEN}> $(NAME) was successfuly compiled 🎉${END}"

$(OBJ_DIR):
			mkdir -p ${OBJ_DIR}

$(OBJ_DIR)/%.o: %.c
			@/bin/echo -n .
			$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
			@$(RM) $(OBJ_DIR)
			@$(MAKE_LIBFT) clean
			@echo "${YELLOW}> All objects files of $(NAME) have been deleted ❌${END}"

fclean:		clean
			@$(RM) $(NAME)
			@$(MAKE_LIBFT) fclean
			@echo "${YELLOW}> Cleaning of $(NAME) has been done ❌${END}"

re:			fclean all

libft:
			@$(MAKE_LIBFT) all bonus

.PHONY: all clean fclean re libft