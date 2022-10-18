NAME := cube
OBJ :=
		obj/main.o \
		obj/parser.o
CFLAGS := -Werror -Wextra -Wall
DEBUG := -fsanitize=address -g3
CC := gcc
LIBFT := includes/libft/libft.a
LIBMLX := includes/MLX42/libmlx42.a
MLXFLAGS := includes/MLX42/libmlx42.a -I -ldl -lglfw3 -pthread -lm
# -ldl -lglfw (or -lglfw3) -pthread -lm

all: $(LIBFT) $(NAME) $(LIBMLX)

$(LIBFT): 
	make -c ./includes/libft

$(LIBMLX):
	make -C ./includes/MLX42

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) $(HEADERS) -o $(NAME) 

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES)
	make clean -C ./includes/libft
	make clean -C ./includes/MLX42

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./includes/libft
	make fclean -C ./includes/MLX42

re: fclean all

.PHONY: clean all fclean re