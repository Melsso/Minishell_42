NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra

OBJ_DIR = obj/
SRC_DIR = src/

SRC		:=	main.c \
			parsing_utils.c \
			parsing_utils2.c \
			my_malloc.c \
			utils.c \
			utils2.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJ	= $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
HEADER = -I ./include -I ../LeakSanitizer
LIBFT = ./libs/libft/libft.a

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(HEADER)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	cd libs/libft && make
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
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

.PHONY: all clean fclean re libft printf gnl
