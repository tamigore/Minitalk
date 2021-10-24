CC = clang

CLIENT = client

SERVEUR = serveur

NAME = $(CLIENT) $(SERVEUR)

LIBFT = libft

HEADER = includes/

SRC_C = client.c

SRC_S = serveur.c

OBJ_C = $(SRC_C:.c=.o)

OBJ_S = $(SRC_S:.c=.o)

OBJS = $(OBJ_C) $(OBJ_S)

CFLAGS = -Wall -Werror -Wextra -I $(HEADER) #-D NUM_THREADS=$(NUM_THREADS)

FLAGS = -L $(LIBFT) -lft

ifeq ($(SANITIZE), 1)
	CFLAGS += -fsanitize=leak -g
endif

all: $(SERVEUR) $(CLIENT)

$(SERVEUR): $(OBJ_S) $(HEADER)
	@ make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_S) $(FLAGS) -o $(SERVEUR)

$(CLIENT): $(OBJ_C) $(HEADER)
	@ make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_C) $(FLAGS) -o $(CLIENT)

norme:
	norminette ./$(LIBFT)
	@echo
	norminette ./$(HEADER)
	@echo
	norminette ./$(SRC_C) $(SRC_S)

bonus: all

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all
