#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>

#include <stdio.h>

void	hook(void *param)
{
	t_vars	*vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		vars->cube->g_img_wall_no->instances[0].y -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		vars->cube->g_img_wall_no->instances[0].y += 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		cast_rays(vars->cube, vars->cube->map, vars->pov);
		vars->pov->facing -= 0.1 * PI;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		cast_rays(vars->cube, vars->cube->map, vars->pov);
		vars->pov->facing += 0.1 * PI;
	}
}

// void	key_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_vars	*vars;

// 	vars = param;
// 	if (keydata.action == MLX_PRESS)

// }

int	game_loop_mlx(t_vars *vars)
{
	//vars->mlx = mlx_init(vars->cube->window_x, vars->cube->window_y, "MLX42", true);
	if (!vars->mlx)
		exit(EXIT_FAILURE);
	//init_mlx_map(vars);
	//mlx_key_hook(vars->mlx, key_hook, vars);
	mlx_loop_hook(vars->mlx, &hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}