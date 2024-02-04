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
SRCS_DIR	= ./src/
HEADER_DIR	= ./includes/
OBJ_DIR 	= .obj

SRCS 		= $(addprefix $(SRCS_DIR),\
				main.c \
				init.c \
				thread.c \
				philo.c \
				fork.c \
				error.c \
				utils.c )

OBJS		= $(SRCS:.c=.o)

CC			= cc
RM			= rm -f
CFLAGS	= -Wall -Wextra -Werror

# LIBFT
LIBFT_DIR	= ./libft
MAKE_LIBFT	= make -s -C $(LIBFT_DIR)
LIBFT_PATH	= $(LIBFT_DIR)/libft.a

NAME		= philo

.c.o:
			@/bin/echo -n .
			@$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) libft
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH) -o $(NAME)
			@echo "\n${GREEN}> $(NAME) was successfuly compiled 🎉${END}"

all: 		$(NAME)

clean:
			@$(RM) $(OBJS)
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