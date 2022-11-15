NAME := cube
OBJFILES :=	obj/main.o \
		obj/parser.o \
		obj/utils.o \
		obj/mlx_loop.o \
		obj/mlx_init.o \
		obj/get_next_line.o \
		obj/get_next_line_utils.o \
		obj/parsing_map.o \
		obj/init_structs.o \
		obj/parsing_map_validate.o \
		obj/scaling_img.o \
		obj/setting_player_rotation.o \
		obj/raycast_utils.o \
		obj/raycast.o
CFLAGS := -Werror -Wextra -Wall -fsanitize=address -g3
DEBUG := 
CC := gcc
LIBFT := includes/libft/libft.a
LIBMLX := includes/MLX42/libmlx42.a
#MLXFLAGS := includes/MLX42/libmlx42.a -ldl -lglfw -pthread -lm -I /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
#MLXFLAGS := includes/MLX42/libmlx42.a -I -ldl -lglfw3 -pthread -lm
# -ldl -lglfw (or -lglfw3) -pthread -lm

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