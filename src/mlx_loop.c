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
	{
		// system("leaks cube");
		mlx_close_window(vars->mlx);
	}
	hook_move_up(vars, moveSpeed);
	hook_move_down(vars, moveSpeed);
	hook_move_left(vars, moveSpeed, dir_perp_x, dir_perp_y);
	hook_move_right(vars, moveSpeed, dir_perp_x, dir_perp_y);
	hook_rotate_left(vars, rotSpeed);
	hook_rotate_right(vars, rotSpeed);

	func(vars, vars->pov);
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
