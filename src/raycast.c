#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>

t_axis	x_raycast(t_axis d, t_axis stdd, t_axis pos, rad angle, char **map)
{
	t_axis	ray;

	//printf("x raycaster before d: x:%f, y:%f\n", pos.x, pos.y);
	ray.x = pos.x + d.x;
	ray.y = pos.y + (tan(angle) * d.x);
	//printf("x raycaster\n");
	while (!check_if_hit(ray, angle, map))
	{
		ray.y += stdd.y;
		if (angle > 0.5 * PI && angle < 1.5 * PI)
			ray.x -= 1;
		else
			ray.x += 1;
	}
	return (ray);
}

t_axis	y_raycast(t_axis d, t_axis stdd, t_axis pos, rad angle, char **map)
{
	t_axis	ray;

	ray.y = pos.y + d.y;
	ray.x = pos.x + (d.y / tan(angle));
	//printf("y raycaster\n");
	while (!check_if_hit(ray, angle, map))
	{
		ray.x += stdd.x;
		if (angle > 0 && angle < PI)
			ray.y += 1;
		else
			ray.y -= 1;
	}
	return (ray);
}

bool	cmp_rays(t_axis xraycast, t_axis yraycast, t_axis pos)
{
	float	xlen;
	float	ylen;

	xlen = sqrt(pow(xraycast.y - pos.y, 2) + pow(xraycast.x - pos.x, 2));
	ylen = sqrt(pow(yraycast.y - pos.y, 2) + pow(yraycast.x - pos.x, 2));
	if (xlen < ylen)
		return (X);
	return (Y);
}

t_axis	find_wall(char **map, t_pov *pov, rad angle)
{
	t_axis	d;
	t_axis	stdd;
	t_axis	xraycast;
	t_axis	yraycast;

	//printf("checking angle for d and stdd: %fPi\n", angle / PI);
	if (angle > 0.5 * PI && angle < 1.5 * PI)
	{
		d.x = -ft_fmod(pov->pos.x, 0);
		stdd.y = -tan(angle);
	}
	else
	{
		d.x = 1 - ft_fmod(pov->pos.x, 0);
		stdd.y = tan(angle);
	}
	if (angle > 0 && angle < PI)
	{
		d.y = 1 - ft_fmod(pov->pos.y, 0);
		stdd.x = 1 / tan(angle);
	}
	else
	{
		d.y = -ft_fmod(pov->pos.y, 0);
		stdd.x = -1 / tan(angle);
	}
	//printf("dx: %f, dy: %f, stddx: %f, stddy: %f\n", d.x, d.y, stdd.x, stdd.y);
	xraycast = x_raycast(d, stdd, pov->pos, angle, map);
	yraycast = y_raycast(d, stdd, pov->pos, angle, map);
	if (cmp_rays(xraycast, yraycast, pov->pos) == X)
		return (xraycast);
	return (yraycast);
}

double calc_scale_vert_line(t_pov *pov, t_ray *ray)
{
	float	linelen;

	linelen = sqrt(pow(ray->end_pos.y - pov->pos.y, 2) + pow(ray->end_pos.x - pov->pos.x, 2));
	// if (linelen > 1)
		linelen = 1 / linelen;

	return (linelen);
}

void	cast_rays(t_cube *cube, char **map, t_pov *pov)
{
	rad		anglestep;
	rad		rayangle;
	float	scale;
	int		i;

	i = 0;
	//map++;
	pov->rays = malloc(sizeof(t_ray) * (SCREEN_X + 1));
	if (pov->rays == NULL)
		error_msg_exit("Error: malloc failure in cast_rays.\n", 1);
	rayangle = pov->facing - (0.5 * pov->fov);
	anglestep = pov->fov / SCREEN_X;
	while (i < SCREEN_X)
	{
		//printf("\ncasting ray with angle: %fPi, column: %d, player position: x:%f, y:%f\n", rayangle / PI, i, pov->pos.x, pov->pos.y);
		pov->rays->end_pos = find_wall(map, pov, round_rad(rayangle));
		pov->rays->wall_ori = find_wall_ori(pov->rays->end_pos, map, round_rad(rayangle));
		//printf("found wall on x:%f, y:%f, ori_wall %c\n", pov->rays->end_pos.x, pov->rays->end_pos.y, pov->rays->wall_ori);
		scale = calc_scale_vert_line(pov, pov->rays);
		print_line(cube, pov->rays, scale, i);
		//fill_col(cube, pov, i, pov->rays->end_pos, rayangle);
		rayangle += anglestep;
		pov->rays++;
		i++;
	}
}