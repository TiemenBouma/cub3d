/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast_calc_walls.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 10:41:36 by tiemen        #+#    #+#                 */
/*   Updated: 2022/11/17 10:41:37 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_wall_ori2(t_ray *ray)
{
	if (ray->dir_x < 0 && ray->dir_y < 0)
	{
		if (ray->wall_side == 0)
			ray->wall_ori = 'S';
		else
			ray->wall_ori = 'W';
	}
	else
	{
		if (ray->wall_side == 0)
			ray->wall_ori = 'S';
		else
			ray->wall_ori = 'E';
	}
}

void	calc_wall_ori(t_ray *ray)
{
	if (ray->dir_x >= 0 && ray->dir_y >= 0)
	{
		if (ray->wall_side == 0)
			ray->wall_ori = 'N';
		else
			ray->wall_ori = 'E';
	}
	else if (ray->dir_x >= 0 && ray->dir_y < 0)
	{
		if (ray->wall_side == 0)
			ray->wall_ori = 'N';
		else
			ray->wall_ori = 'W';
	}
	else
		calc_wall_ori2(ray);
}

void	calc_wall_x(t_ray *ray, t_pov *pov)
{
	ray->wall_x = 0;
	if (ray->wall_side == 0)
		ray->wall_x = pov->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = pov->pos_x + ray->perp_wall_dist * ray->dir_x;
}
