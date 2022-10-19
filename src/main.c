#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>


int main(void)
{
	t_vars	vars;
	t_cube	cube;

	vars.cube = &cube;
	cube.window_x = 1000;
	cube.window_y = 1000;
	init_struct(&vars);
	game_loop_mlx(&vars);

	return (0);
}