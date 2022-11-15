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
	double	dir_perp_x = vars->pov->dir_y * -1;
	double	dir_perp_y = vars->pov->dir_x;
	if (vars->gamecycle % 50 == 0)
	{
		printf("STATUS: delta time %f\n", (vars->mlx->delta_time));
		printf("STATUS: FPS %d\n", (int)(1 / vars->mlx->delta_time));
		printf("STATUS: x %f y %f\n", vars->pov->pos_x, vars->pov->pos_y);
		printf("STATUS: movespeed %f rotspeed %f\n", moveSpeed, rotSpeed);
		//printf("DEBUG: x %f y %f\n", vars->cube->pov->rays[0]., vars->pov->pos_y);

	}
	//printf("Gamecycle: %d\n", vars->gamecycle);

	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	//UP
	
	//DOWN
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
	{
		if(vars->cube->map[(int)(vars->pov->pos_y + 0.1)][(int)(vars->pov->pos_x - vars->pov->dir_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - 0.1)][(int)(vars->pov->pos_x - vars->pov->dir_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x - vars->pov->dir_x * moveSpeed + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x - vars->pov->dir_x * moveSpeed - 0.1)] != '1') 
			vars->pov->pos_x -= vars->pov->dir_x * moveSpeed;
		if(vars->cube->map[(int)(vars->pov->pos_y - vars->pov->dir_y * moveSpeed + 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - vars->pov->dir_y * moveSpeed - 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - vars->pov->dir_y * moveSpeed)][(int)(vars->pov->pos_x + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - vars->pov->dir_y * moveSpeed)][(int)(vars->pov->pos_x - 0.1)] != '1') 
			vars->pov->pos_y -= vars->pov->dir_y * moveSpeed;
		else
		{
			printf("hit wall\n");
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		if(vars->cube->map[(int)(vars->pov->pos_y + 0.1)][(int)(vars->pov->pos_x - dir_perp_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - 0.1)][(int)(vars->pov->pos_x - dir_perp_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x - dir_perp_x * moveSpeed + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x - dir_perp_x * moveSpeed - 0.1)] != '1') 
			vars->pov->pos_x -= dir_perp_x * moveSpeed;
		if(vars->cube->map[(int)(vars->pov->pos_y - dir_perp_y * moveSpeed + 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - dir_perp_y * moveSpeed - 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - dir_perp_y * moveSpeed)][(int)(vars->pov->pos_x + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - dir_perp_y * moveSpeed)][(int)(vars->pov->pos_x - 0.1)] != '1') 
			vars->pov->pos_y -= dir_perp_y * moveSpeed;
		else
		{
			printf("hit wall\n");
		}
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		if(vars->cube->map[(int)(vars->pov->pos_y + 0.1)][(int)(vars->pov->pos_x + dir_perp_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y - 0.1)][(int)(vars->pov->pos_x + dir_perp_x * moveSpeed)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x + dir_perp_x * moveSpeed + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y)][(int)(vars->pov->pos_x + dir_perp_x * moveSpeed - 0.1)] != '1') 
			vars->pov->pos_x += dir_perp_x * moveSpeed;
		if(vars->cube->map[(int)(vars->pov->pos_y + dir_perp_y * moveSpeed + 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y + dir_perp_y * moveSpeed - 0.1)][(int)(vars->pov->pos_x)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y + dir_perp_y * moveSpeed)][(int)(vars->pov->pos_x + 0.1)] != '1'
			&& vars->cube->map[(int)(vars->pov->pos_y + dir_perp_y * moveSpeed)][(int)(vars->pov->pos_x - 0.1)] != '1') 
			vars->pov->pos_y += dir_perp_y * moveSpeed;
		else
		{
			printf("hit wall\n");
		}
	}
	//LEFT rotate
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = vars->pov->dir_x;
		vars->pov->dir_x = vars->pov->dir_x * cos(rotSpeed) - vars->pov->dir_y * sin(rotSpeed);
		vars->pov->dir_y = oldDirX * sin(rotSpeed) + vars->pov->dir_y * cos(rotSpeed);
		double oldPlaneX = vars->pov->plane_x;
		vars->pov->plane_x = vars->pov->plane_x * cos(rotSpeed) - vars->pov->plane_y * sin(rotSpeed);
		vars->pov->plane_y = oldPlaneX * sin(rotSpeed) + vars->pov->plane_y * cos(rotSpeed);
		// printf("currently on map[%d][%d]: %c\n", (int)(vars->pov->pos_y), (int)(vars->pov->pos_x), vars->cube->map[(int)vars->pov->pos_y][(int)vars->pov->pos_x]);
		// printf("plane x %f, plane y %f\n\n", vars->pov->plane_x, vars->pov->plane_y);
		// printf("dir x %f, dir y %f\n\n", vars->pov->dir_x, vars->pov->dir_y);
	}

//RIGHT reotate
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	{
      //both camera direction and camera plane must be rotated
    double oldDirX = vars->pov->dir_x;
    vars->pov->dir_x = vars->pov->dir_x * cos(-rotSpeed) - vars->pov->dir_y * sin(-rotSpeed);
    vars->pov->dir_y = oldDirX * sin(-rotSpeed) + vars->pov->dir_y * cos(-rotSpeed);
    double oldPlaneX = vars->pov->plane_x;
    vars->pov->plane_x = vars->pov->plane_x * cos(-rotSpeed) - vars->pov->plane_y * sin(-rotSpeed);
    vars->pov->plane_y = oldPlaneX * sin(-rotSpeed) + vars->pov->plane_y * cos(-rotSpeed);
	// printf("plane x %f, plane y %f\n\n", vars->pov->plane_x, vars->pov->plane_y);
	}

	//LEFT

	raycaster(vars, vars->pov);
	//cast_rays(vars->cube, vars->cube->map, vars->pov);
	mlx_image_to_window(vars->mlx, vars->cube->g_img_DEMO, 0, 0);


}

int    game_loop_mlx(t_vars *vars)
{
       if (!vars->mlx)
               exit(EXIT_FAILURE);
       //mlx_key_hook(vars->mlx, hook, vars);

       mlx_loop_hook(vars->mlx, &hook, vars);

       mlx_loop(vars->mlx);

       mlx_terminate(vars->mlx);
       return (EXIT_SUCCESS);
}
