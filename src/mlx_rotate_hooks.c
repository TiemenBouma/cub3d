/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_rotate_hooks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:41:15 by tiemen            #+#    #+#             */
/*   Updated: 2022/11/23 10:57:54 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

void	rotate_right(t_pov *pov, double old_dir_x,
			double old_plane_x, double rotSpeed)
{
	pov->dir_x = pov->dir_x * cos(rotSpeed)
		- pov->dir_y * sin(rotSpeed);
	pov->dir_y = old_dir_x * sin(rotSpeed)
		+ pov->dir_y * cos(rotSpeed);
	pov->plane_x = pov->plane_x * cos(rotSpeed)
		- pov->plane_y * sin(rotSpeed);
	pov->plane_y = old_plane_x * sin(rotSpeed)
		+ pov->plane_y * cos(rotSpeed);
}

void	rotate_left(t_pov *pov, double old_dir_x,
			double old_plane_x, double rotSpeed)
{
	pov->dir_x = pov->dir_x * cos(-rotSpeed)
		- pov->dir_y * sin(-rotSpeed);
	pov->dir_y = old_dir_x * sin(-rotSpeed)
		+ pov->dir_y * cos(-rotSpeed);
	pov->plane_x = pov->plane_x * cos(-rotSpeed)
		- pov->plane_y * sin(-rotSpeed);
	pov->plane_y = old_plane_x * sin(-rotSpeed)
		+ pov->plane_y * cos(-rotSpeed);
}

void	hook_rotate_right(t_vars *vars, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vars->pov->dir_x;
	old_plane_x = vars->pov->plane_x;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		rotate_right(vars->pov, old_dir_x, old_plane_x, rotSpeed);
}

void	hook_rotate_left(t_vars *vars, double rotSpeed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vars->pov->dir_x;
	old_plane_x = vars->pov->plane_x;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		rotate_left(vars->pov, old_dir_x, old_plane_x, rotSpeed);
}

void	hook_cursor_rotate(t_vars *vars, double rotSpeed)
{
	int		old_x;
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vars->pov->dir_x;
	old_plane_x = vars->pov->plane_x;
	old_x = vars->cube->cursorx;
	mlx_get_mouse_pos(vars->mlx, &vars->cube->cursorx, &vars->cube->cursory);
	if (old_x < vars->cube->cursorx)
		rotate_right(vars->pov, old_dir_x, old_plane_x, rotSpeed);
	else if (old_x > vars->cube->cursorx)
		rotate_left(vars->pov, old_dir_x, old_plane_x, rotSpeed);
	if (vars->cube->cursorx < 0)
	{
		mlx_set_mouse_pos(vars->mlx, vars->cube->window_x, vars->cube->cursory);
		mlx_get_mouse_pos(vars->mlx, &vars->cube->cursorx,
			&vars->cube->cursory);
	}
	else if (vars->cube->cursorx > vars->cube->window_x)
	{
		mlx_set_mouse_pos(vars->mlx, 0, vars->cube->cursory);
		mlx_get_mouse_pos(vars->mlx, &vars->cube->cursorx,
			&vars->cube->cursory);
	}
}
