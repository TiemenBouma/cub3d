#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>

#include <stdio.h>

void	hook(void *param)
{
	t_vars	*vars;

	vars = param;
	mlx_delete_image(vars->mlx, vars->cube->g_img_DEMO);
	vars->cube->g_img_DEMO = mlx_new_image(vars->mlx, SCREEN_X, SCREEN_Y);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		vars->pov->pos.x += 0.1 * cos(vars->pov->facing);
		vars->pov->pos.y += 0.1 * sin(vars->pov->facing);
		cast_rays(vars->cube, vars->cube->map, vars->pov);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		vars->pov->pos.x -= 0.1 * cos(vars->pov->facing);
		vars->pov->pos.y -= 0.1 * sin(vars->pov->facing);
		cast_rays(vars->cube, vars->cube->map, vars->pov);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->pov->facing -= 0.01 * PI;
		cast_rays(vars->cube, vars->cube->map, vars->pov);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->pov->facing += 0.01 * PI;
		cast_rays(vars->cube, vars->cube->map, vars->pov);
	}
	mlx_image_to_window(vars->mlx, vars->cube->g_img_DEMO, 0, 0);

}

int	game_loop_mlx(t_vars *vars)
{
	if (!vars->mlx)
		exit(EXIT_FAILURE);
	mlx_loop_hook(vars->mlx, &hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}

// void	hook(void *param)
// {
// 	t_vars	*vars;

// 	vars = param;
// 	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(vars->mlx);
// 	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
// 		vars->cube->g_img_wall_no->instances[0].y -= 5;
// 	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
// 		vars->cube->g_img_wall_no->instances[0].y += 5;
// 	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
// 		vars->cube->g_img_wall_no->instances[0].x -= 5;
// 	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
// 		vars->cube->g_img_wall_no->instances[0].x += 5;
// }

