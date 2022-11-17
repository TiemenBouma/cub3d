/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 10:41:08 by tiemen        #+#    #+#                 */
/*   Updated: 2022/11/17 10:54:28 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>
//#include <time.h>

//#include <stdio.h>

void	hook( void *param)
{
	t_vars	*vars;
	double	move_speed;
	double	rot_speed;
	double	dir_perp_x;
	double	dir_perp_y;

	vars = param;
	move_speed = vars->mlx->delta_time * 5.0;
	rot_speed = vars->mlx->delta_time * 3.0;
	dir_perp_x = vars->pov->dir_y * -1;
	dir_perp_y = vars->pov->dir_x;
	mlx_delete_image(vars->mlx, vars->cube->g_img_demo);
	vars->cube->g_img_demo = mlx_new_image(vars->mlx, SCREEN_X, SCREEN_Y);
	hook_move_up(vars, move_speed);
	hook_move_down(vars, move_speed);
	hook_move_left(vars, move_speed, dir_perp_x, dir_perp_y);
	hook_move_right(vars, move_speed, dir_perp_x, dir_perp_y);
	hook_rotate_left(vars, rot_speed);
	hook_rotate_right(vars, rot_speed);
	hook_cursor_rotate(vars, rot_speed);
	raycaster(vars, vars->pov);
	mlx_image_to_window(vars->mlx, vars->cube->g_img_demo, 0, 0);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
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
