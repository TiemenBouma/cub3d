/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_move_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:41:12 by tiemen            #+#    #+#             */
/*   Updated: 2022/11/21 14:14:50 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	hook_move_up(t_vars *vars, double moveSpeed)
{
	double	*posx;
	double	*posy;
	double	*dirx;
	double	*diry;
	char	**map;

	posx = &vars->pov->pos_x;
	posy = &vars->pov->pos_y;
	dirx = &vars->pov->dir_x;
	diry = &vars->pov->dir_y;
	map = vars->cube->map;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W)
		|| mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
		if (map[(int)(*posy + 0.1)][(int)(*posx + *dirx * moveSpeed)] != '1'
			&& map[(int)(*posy - 0.1)][(int)(*posx + *dirx * moveSpeed)] != '1'
			&& map[(int)(*posy)][(int)(*posx + *dirx * moveSpeed + 0.1)] != '1'
			&& map[(int)(*posy)][(int)(*posx + *dirx * moveSpeed - 0.1)] != '1')
			*posx += *dirx * moveSpeed;
		if (map[(int)(*posy + *diry * moveSpeed + 0.1)][(int)(*posx)] != '1'
			&& map[(int)(*posy + *diry * moveSpeed - 0.1)][(int)(*posx)] != '1'
			&& map[(int)(*posy + *diry * moveSpeed)][(int)(*posx + 0.1)] != '1'
			&& map[(int)(*posy + *diry * moveSpeed)][(int)(*posx - 0.1)] != '1')
			*posy += *diry * moveSpeed;
	}
}

void	hook_move_down(t_vars *vars, double moveSpeed)
{
	double	*posx;
	double	*posy;
	double	*dirx;
	double	*diry;
	char	**map;

	posx = &vars->pov->pos_x;
	posy = &vars->pov->pos_y;
	dirx = &vars->pov->dir_x;
	diry = &vars->pov->dir_y;
	map = vars->cube->map;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S)
		|| mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	{
		if (map[(int)(*posy + 0.1)][(int)(*posx - *dirx * moveSpeed)] != '1'
			&& map[(int)(*posy - 0.1)][(int)(*posx - *dirx * moveSpeed)] != '1'
			&& map[(int)(*posy)][(int)(*posx - *dirx * moveSpeed + 0.1)] != '1'
			&& map[(int)(*posy)][(int)(*posx - *dirx * moveSpeed - 0.1)] != '1')
			*posx -= *dirx * moveSpeed;
		if (map[(int)(*posy - *diry * moveSpeed + 0.1)][(int)(*posx)] != '1'
			&& map[(int)(*posy - *diry * moveSpeed - 0.1)][(int)(*posx)] != '1'
			&& map[(int)(*posy - *diry * moveSpeed)][(int)(*posx + 0.1)] != '1'
			&& map[(int)(*posy - *diry * moveSpeed)][(int)(*posx - 0.1)] != '1')
			*posy -= *diry * moveSpeed;
	}
}

void	hook_move_right(t_vars *vars, double moveSpeed,
			double perpx, double perpy)
{
	double	*posx;
	double	*posy;
	char	**map;

	posx = &vars->pov->pos_x;
	posy = &vars->pov->pos_y;
	map = vars->cube->map;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		if (map[(int)(*posy + 0.1)][(int)(*posx + perpx * moveSpeed)] != '1'
			&& map[(int)(*posy - 0.1)][(int)(*posx + perpx * moveSpeed)] != '1'
			&& map[(int)(*posy)][(int)(*posx + perpx * moveSpeed + 0.1)] != '1'
			&& map[(int)(*posy)][(int)(*posx + perpx * moveSpeed - 0.1)] != '1')
			*posx += perpx * moveSpeed;
		if (map[(int)(*posy + perpy * moveSpeed + 0.1)][(int)(*posx)] != '1'
			&& map[(int)(*posy + perpy * moveSpeed - 0.1)][(int)(*posx)] != '1'
			&& map[(int)(*posy + perpy * moveSpeed)][(int)(*posx + 0.1)] != '1'
			&& map[(int)(*posy + perpy * moveSpeed)][(int)(*posx - 0.1)] != '1')
			*posy += perpy * moveSpeed;
	}
}

void	hook_move_left(t_vars *vars, double moveSpeed,
			double perpx, double perpy)
{
	double	*posx;
	double	*posy;
	char	**map;

	posx = &vars->pov->pos_x;
	posy = &vars->pov->pos_y;
	map = vars->cube->map;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
	{
		if (map[(int)(*posy + 0.1)][(int)(*posx - perpx * moveSpeed)] != '1'
			&& map[(int)(*posy - 0.1)][(int)(*posx - perpx * moveSpeed)] != '1'
			&& map[(int)(*posy)][(int)(*posx - perpx * moveSpeed + 0.1)] != '1'
			&& map[(int)(*posy)][(int)(*posx - perpx * moveSpeed - 0.1)] != '1')
			*posx -= perpx * moveSpeed;
		if (map[(int)(*posy - perpy * moveSpeed + 0.1)][(int)(*posx)] != '1'
			&& map[(int)(*posy - perpy * moveSpeed - 0.1)][(int)(*posx)] != '1'
			&& map[(int)(*posy - perpy * moveSpeed)][(int)(*posx + 0.1)] != '1'
			&& map[(int)(*posy - perpy * moveSpeed)][(int)(*posx - 0.1)] != '1')
			*posy -= perpy * moveSpeed;
	}
}
