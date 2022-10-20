#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>

#include <stdio.h>

int main(int argc, char **argv)
{
	t_vars	vars;
	t_cube	cube;
	t_file	file;
	(void)argc;
	vars.argv = argv;
	vars.cube = &cube;
	vars.file = &file;
	cube.window_x = 1000;
	cube.window_y = 1000;
	printf("DEBUG\n");
	parsing(&vars);
	printf("DEBUG3\n");
	init_struct(&vars);
	game_loop_mlx(&vars);

	return (0);
}