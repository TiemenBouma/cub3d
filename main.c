#include "includes/MLX42/include/MLX42/MLX42.h"
#include "includes/cub3d.h"
#include <stdlib.h>

// void	key_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_vars	*vars;

// 	vars = param;
// 	if (keydata.action == MLX_PRESS)

// }

int	game_loop_mlx(t_vars *vars)
{
	vars->mlx = mlx_init(vars->cube->window_x, vars->cube->window_y, "MLX42", true);
	if (!vars->mlx)
		exit(EXIT_FAILURE);
	//init_mlx_map(vars);
	//mlx_key_hook(vars->mlx, key_hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}

int	init_struct(t_cube *cube)
{
	cube->ceilling_rgb[0] = 1;
	cube->ceilling_rgb[1] = 1;
	cube->ceilling_rgb[2] = 1;
	cube->floor_rgb[0] = 255;
	cube->floor_rgb[1] = 255;
	cube->floor_rgb[2] = 255;
}

int main(void)
{
	t_vars	vars;
	t_cube	cube;

	vars.cube = &cube;
	cube.window_x = 1000;
	cube.window_y = 1000;
	game_loop_mlx(&vars);


}