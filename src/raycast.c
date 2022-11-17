/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 10:41:54 by tiemen        #+#    #+#                 */
/*   Updated: 2022/11/17 11:05:19 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
//#include "../includes/libft/libft.h"
//#include <stdlib.h>

void	raycaster(t_vars *vars, t_pov *pov)
{
	t_ray	ray;
	int		x;
	double	camera_x;

	x = 0;
	while (x < SCREEN_X)
	{
		camera_x = 2 * x / (double) SCREEN_X - 1;
		camera_x *= -1;
		calc_raydir(&ray, pov, camera_x);
		ray.map_x = (int)pov->pos_x;
		ray.map_y = (int)pov->pos_y;
		calc_delta_dist(&ray);
		calc_initial_side_dist(&ray, pov);
		calc_side_dist(&ray, vars->cube->map);
		calc_perp_wall_dist(&ray);
		calc_wall_ori(&ray);
		calc_wall_x(&ray, pov);
		ray.scale = 1 / ray.perp_wall_dist;
		print_line(vars->cube, x, &ray);
		x++;
	}
}
