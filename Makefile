NAME := cube
OBJ :=	obj/main.o \
		obj/parser.o \
		obj/utils.o \
		obj/mlx_loop.o \
		obj/mlx_init.o \
		obj/get_next_line.o \
		obj/get_next_line_utils.o \
		obj/parsing_validation.o \
		obj/parsing_map.o \
		obj/init_structs.o \
		obj/parsing_map_validate.o \
		obj/testing.o
CFLAGS := -Werror -Wextra -Wall
DEBUG := -fsanitize=address -g3
CC := gcc
LIBFT := includes/libft/libft.a
LIBMLX := includes/MLX42/libmlx42.a
MLXFLAGS := includes/MLX42/libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
#MLXFLAGS := includes/MLX42/libmlx42.a -I -ldl -lglfw3 -pthread -lm
# -ldl -lglfw (or -lglfw3) -pthread -lm

all: $(LIBFT) $(LIBMLX) $(NAME)

$(LIBFT): 
	make -C ./includes/libft

$(LIBMLX):
	make -C ./includes/MLX42

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJ) $(LIBFT) $(LIBMLX) $(\) -o $(NAME) 

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