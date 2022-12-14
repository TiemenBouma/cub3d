NAME := cub3D
OBJFILES :=	obj/main.o \
			obj/get_next_line_utils.o \
			obj/get_next_line.o \
			obj/init_structs.o \
			obj/mlx_init.o \
			obj/mlx_loop.o \
			obj/mlx_move_hooks.o \
			obj/mlx_rotate_hooks.o \
			obj/parsing.o \
			obj/parsing_map.o \
			obj/parsing_map2.o \
			obj/parsing_map_validate.o \
			obj/parsing_utils.o \
			obj/raycast.o \
			obj/raycast_calc.o \
			obj/raycast_calc_walls.o \
			obj/raycast_texture_line.o \
			obj/raycast_texture_line2.o \
			obj/raycast_utils.o \
			obj/setting_player_rotation.o \
			obj/utils.o
CFLAGS := -Werror -Wextra -Wall
DEBUG := -fsanitize=address -g3
CC := cc
LIBFT := includes/libft/libft.a
LIBMLX := includes/MLX42/libmlx42.a
MLXFLAGS_LINUX := includes/MLX42/libmlx42.a -ldl -lglfw -pthread -lm -I /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
MLXFLAGS := -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
all: $(LIBFT) $(LIBMLX) $(NAME)

$(LIBFT): 
	make -C ./includes/libft

$(LIBMLX):
	make -C ./includes/MLX42

$(NAME): $(OBJFILES)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJFILES) $(LIBFT) $(LIBMLX) $(\) -o $(NAME) 

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