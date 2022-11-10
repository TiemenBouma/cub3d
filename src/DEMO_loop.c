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

	double moveSpeed = vars->mlx->delta_time * 5.0; //the constant value is in squares/second
    double rotSpeed = vars->mlx->delta_time * 3.0; //the constant value is in radians/second
	if (vars->gamecycle % 10 == 0)
	{
		printf("DEUBG: FPS %d\n", (int)(1 / vars->mlx->delta_time));
		printf("DEBUG: x %f y %f\n", vars->pov->pos.x, vars->pov->pos.y);
		//printf("DEBUG: x %f y %f\n", vars->cube->pov->rays[0]., vars->pov->pos.y);

	}
	//printf("Gamecycle: %d\n", vars->gamecycle);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		if(vars->cube->map[(int)(vars->pov->pos.x + vars->pov->dir_x * moveSpeed)][(int)(vars->pov->pos.y)] == 0) 
			vars->pov->pos.x += vars->pov->dir_x * moveSpeed;
		if(vars->cube->map[(int)(vars->pov->pos.x)][(int)(vars->pov->pos.y + vars->pov->dir_y * moveSpeed)] == 0) 
			vars->pov->pos.y += vars->pov->dir_y * moveSpeed;
		else
		{
			printf("hit wall\n");
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		if(vars->cube->map[(int)(vars->pov->pos.x + vars->pov->dir_x * moveSpeed)][(int)(vars->pov->pos.y)] == 0) 
			vars->pov->pos.x += vars->pov->dir_x * moveSpeed;
		if(vars->cube->map[(int)(vars->pov->pos.x)][(int)(vars->pov->pos.y + vars->pov->dir_y * moveSpeed)] == 0) 
			vars->pov->pos.y += vars->pov->dir_y * moveSpeed;
		else
		{
			printf("hit wall\n");
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
      //both camera direction and camera plane must be rotated
      double oldDirX = vars->pov->dir_x;
      vars->pov->dir_x = vars->pov->dir_x * cos(rotSpeed) - vars->pov->dir_y * sin(rotSpeed);
      vars->pov->dir_y = oldDirX * sin(rotSpeed) + vars->pov->dir_y * cos(rotSpeed);
      double oldPlaneX = vars->pov->plane_x;
      vars->pov->plane_x = vars->pov->plane_x * cos(rotSpeed) - vars->pov->plane_y * sin(rotSpeed);
      vars->pov->plane_y = oldPlaneX * sin(rotSpeed) + vars->pov->plane_y * cos(rotSpeed);
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
      //both camera direction and camera plane must be rotated
      double oldDirX = vars->pov->dir_x;
      vars->pov->dir_x = vars->pov->dir_x * cos(-rotSpeed) - vars->pov->dir_y * sin(-rotSpeed);
      vars->pov->dir_y = oldDirX * sin(-rotSpeed) + vars->pov->dir_y * cos(-rotSpeed);
      double oldPlaneX = vars->pov->plane_x;
      vars->pov->plane_x = vars->pov->plane_x * cos(-rotSpeed) - vars->pov->plane_y * sin(-rotSpeed);
      vars->pov->plane_y = oldPlaneX * sin(-rotSpeed) + vars->pov->plane_y * cos(-rotSpeed);
	}
	func(vars, vars->pov);
	//cast_rays(vars->cube, vars->cube->map, vars->pov);
	mlx_image_to_window(vars->mlx, vars->cube->g_img_DEMO, 0, 0);

}