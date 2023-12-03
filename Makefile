NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj/
SRC_DIR = src/

SRC		:=	main.c \
			parsing_utils.c \
			parsing_utils1.c \
			parsing_utils2.c \
			exe.c \
			exe_utils.c \
			expand.c \
			expand_utils.c \
			redirection.c \
			redirection_utils.c \
			heredoc.c \
			clean.c \
			my_malloc.c \
			tree_utils.c \
			tree_utils1.c \
			split_utils.c \
			split_utils1.c \
			export.c \
			unset.c \
			cd.c \
			echo.c \
			builtins.c \
			utils.c \
			error.c \
			signals.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJ	= $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
HEADER = -I ./include
LIBFT = ./libs/libft/libft.a

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(HEADER)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	cd libs/libft && make
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline $(HEADER) -o $(NAME)
	clear

clean:
	cd libs/libft && make clean
	rm -rf $(OBJ_DIR)
	clear

fclean: clean
	cd libs/libft && make fclean
	rm -f $(NAME)
	clear

re: fclean all

.PHONY: all clean fclean re libft
