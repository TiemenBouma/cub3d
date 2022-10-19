#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>


int main(int argc, char **argv)
{
	t_vars	vars;
	t_cube	cube;
	(void)argc;
	cube.argv = argv;
	vars.cube = &cube;
	cube.window_x = 1000;
	cube.window_y = 1000;

	//parsing(&vars);

	init_struct(&vars);
	game_loop_mlx(&vars);

	return (0);
}