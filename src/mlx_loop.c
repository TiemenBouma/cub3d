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
	mlx_delete_image(vars->mlx, vars->cube->g_img_DEMO);
	vars->cube->g_img_DEMO = mlx_new_image(vars->mlx, SCREEN_X, SCREEN_Y);
	vars->gamecycle++;
	if (vars->gamecycle % 10 == 0)
	{
		printf("FPS %d\n", (int)(1 / vars->mlx->delta_time));
	}
	//printf("Gamecycle: %d\n", vars->gamecycle);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		int y = (int)(vars->pov->pos.y + (0.2 * sin(vars->pov->facing)));
		int x = (int)(vars->pov->pos.x + (0.2 * cos(vars->pov->facing)));
	//	printf("DEBUG: MAP c %c\n", vars->cube->map[y][x]);
	//	printf("DEBUG: delta x = %d, delta y = %d\n", x, y);
		if (vars->cube->map[y][x] != '1')
		{
			vars->pov->pos.x += 0.1 * cos(vars->pov->facing);
			vars->pov->pos.y += 0.1 * sin(vars->pov->facing);
		}
		else{
			printf("hit wall\n");
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		int y = (int)(vars->pov->pos.y - (0.2 * sin(vars->pov->facing)));
		int x = (int)(vars->pov->pos.x - (0.2 * cos(vars->pov->facing)));
	//	printf("DEBUG: MAP c %c\n", vars->cube->map[y][x]);
		//printf("DEBUG: delta x = %d, delta y = %d\n", x, y);
		if (vars->cube->map[y][x] != '1')
		{
			vars->pov->pos.x -= 0.1 * cos(vars->pov->facing);
			vars->pov->pos.y -= 0.1 * sin(vars->pov->facing);
		}
		else{
			printf("hit wall\n");
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		vars->pov->facing -= 0.03 * PI;
		//cast_rays(vars->cube, vars->cube->map, vars->pov);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
		vars->pov->facing += 0.03 * PI;
	}
	cast_rays(vars->cube, vars->cube->map, vars->pov);
	mlx_image_to_window(vars->mlx, vars->cube->g_img_DEMO, 0, 0);

}

int	game_loop_mlx(t_vars *vars)
{
	if (!vars->mlx)
		exit(EXIT_FAILURE);
	//mlx_key_hook(vars->mlx, hook, vars);
	mlx_loop_hook(vars->mlx, &hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}
