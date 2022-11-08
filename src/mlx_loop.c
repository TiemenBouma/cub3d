#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>
#include <time.h>

#include <stdio.h>

void	hook( void *param)//mlx_key_data_t keydata,
{
	t_vars	*vars;
	//(void)keydata;
	vars = param;
	if (vars->cube->g_img_DEMO != NULL)
	{
		mlx_delete_image(vars->mlx, vars->cube->g_img_DEMO);
		vars->cube->g_img_DEMO = NULL;
	}
	vars->cube->g_img_DEMO = mlx_new_image(vars->mlx, vars->cube->window_x, vars->cube->window_y);
	vars->gamecycle++;
	if (vars->gamecycle % 10 == 0)
	{
		printf("DEUBG: FPS %d\n", (int)(1 / vars->mlx->delta_time));
		printf("DEBUG: x %f y %f\n", vars->pov->pos.x, vars->pov->pos.y);
	}
	//printf("Gamecycle: %d\n", vars->gamecycle);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		int y = (int)(vars->pov->pos.y + (0.21 * sin(vars->pov->facing)));
		int x = (int)(vars->pov->pos.x + (0.21 * cos(vars->pov->facing)));
	//	printf("DEBUG: MAP c %c\n", vars->cube->map[y][x]);
	//	printf("DEBUG: delta x = %d, delta y = %d\n", x, y);
		if (vars->cube->map[y][x] != '1')
		{
			vars->pov->pos.x += 0.2 * cos(vars->pov->facing);
			vars->pov->pos.y += 0.2 * sin(vars->pov->facing);
		}
		else if (vars->cube->map[y][(int)vars->pov->pos.x] != '1')
			vars->pov->pos.y += 0.2 * sin(vars->pov->facing);
		else if (vars->cube->map[(int)vars->pov->pos.y][x] != '1')
			vars->pov->pos.x += 0.2 * cos(vars->pov->facing);
		else
		{
			printf("hit wall\n");
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		int y = (int)(vars->pov->pos.y - (0.21 * sin(vars->pov->facing)));
		int x = (int)(vars->pov->pos.x - (0.21 * cos(vars->pov->facing)));
	//	printf("DEBUG: MAP c %c\n", vars->cube->map[y][x]);
		//printf("DEBUG: delta x = %d, delta y = %d\n", x, y);
		if (vars->cube->map[y][x] != '1')
		{
			vars->pov->pos.x -= 0.2 * cos(vars->pov->facing);
			vars->pov->pos.y -= 0.2 * sin(vars->pov->facing);
		}
		else if (vars->cube->map[y][(int)vars->pov->pos.x] != '1')
			vars->pov->pos.y -= 0.2 * sin(vars->pov->facing);
		else if (vars->cube->map[(int)vars->pov->pos.y][x] != '1')
			vars->pov->pos.x -= 0.2 * cos(vars->pov->facing);
		else
		{
			printf("hit wall\n");
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->pov->facing -= 0.05 * PI;
		//cast_rays(vars->cube, vars->cube->map, vars->pov);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->pov->facing += 0.05 * PI;
	}
	cast_rays(vars->cube, vars->cube->map, vars->pov);
	mlx_image_to_window(vars->mlx, vars->cube->g_img_DEMO, 0, 0);

}

void resize_hook(int32_t width, int32_t height, void* param)
{
	t_vars	*vars;

	vars = param;

	if (vars->cube->g_img_DEMO != NULL)
	{
		mlx_delete_image(vars->mlx, vars->cube->g_img_DEMO);
		vars->cube->g_img_DEMO = NULL;
	}
	vars->cube->g_img_DEMO = mlx_new_image(vars->mlx, vars->cube->window_x, vars->cube->window_y);
	
	mlx_delete_image(vars->mlx, vars->cube->g_img_ceilling);
	mlx_delete_image(vars->mlx, vars->cube->g_img_floor);
	vars->cube->window_x = width;
	vars->cube->window_y = height;
	make_floor_ceilling(vars->mlx, vars->cube);
	cast_rays(vars->cube, vars->cube->map, vars->pov);
	vars->pov->fov = PI * 0.6;//(0.6 * (double)(vars->cube->window_x / 1024)); // Needs to be fixed
	printf("DEBUG: resize %d %d\n", width, height);
}

int	game_loop_mlx(t_vars *vars)
{
	if (!vars->mlx)
		exit(EXIT_FAILURE);
	//mlx_key_hook(vars->mlx, hook, vars);
	//mlx_resize_hook(vars->mlx, &resize_hook, vars);
	mlx_loop_hook(vars->mlx, &hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}
