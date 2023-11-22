NAME = minishell
CC = cc
CFLAGS = 

OBJ_DIR = obj/
SRC_DIR = src/

SRC		:=	main.c \
			parsing_utils.c \
			parsing_utils2.c \
			exe_utils.c \
			expand.c \
			redirection.c \
			redirection_utils.c \
			clean.c \
			my_malloc.c \
			tree_utils.c \
			tree_utils2.c \
			tree_utils3.c \
			export.c \
			unset.c \
			cd.c \
			echo.c \
			builtins.c \

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

clean:
	cd libs/libft && make clean
	rm -rf $(OBJ_DIR)
	clear

fclean: clean
	cd libs/libft && make fclean
	rm -f $(NAME)
	clear

re: fclean all

.PHONY: all clean fclean re libft printf gnl
