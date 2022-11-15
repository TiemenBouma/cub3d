#include "../includes/cub3d.h"

void	calc_raydir(t_ray *ray, t_pov *pov, double camera_x)
{
	ray->dir_x = pov->dir_x + pov->plane_x * camera_x;
	ray->dir_y = pov->dir_y + pov->plane_y * camera_x;
}

void	calc_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = ft_abs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = ft_abs(1 / ray->dir_y);
}

void	calc_side_dist(t_ray *ray, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->wall_side = 0;
		}
		else
		{
			ray->sidedist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->wall_side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	calc_initial_side_dist(t_ray *ray, t_pov *pov)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (pov->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - pov->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (pov->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - pov->pos_y) * ray->delta_dist_y;
	}
}

void	calc_perp_wall_dist(t_ray *ray)
{
	if (ray->wall_side == 0)
		ray->perp_wall_dist = (ray->sidedist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->sidedist_y - ray->delta_dist_y);
}
