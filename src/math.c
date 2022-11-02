#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>

float	round_rad(rad rad)
{
	while (rad < 0)
		rad += 2 * PI;
	while (rad > 2 * PI)
		rad -= 2 * PI;
	return (rad);
}

void	print_field(char **field)
{
	int	i;

	i = 0;
	while (field[i] != NULL)
	{
		printf("%s\n", field[i]);
		i++;
	}
}

float ft_fmod(float f, bool exclude_zero)
{
	while (f <= -1 || f >= 1)
	{
		if (f < 0)
			f += 1;
		else
			f -= 1;
	}
	if (exclude_zero == 1 && f == 0)
		f = 1;
	return (f);
}

bool	is_player(char player)
{
	return (player == 'N' || player == 'E' || player == 'S' || player == 'W');
}

double	calc_facing(char player)
{
	if(player == 'N')
		return (1.5 * PI);
	if(player == 'E')
		return (0);
	if(player == 'S')
		return (0.5 * PI);
	if(player == 'W')
		return (1 * PI);
	return (1);
}

void	find_playpos(t_cube *cube, t_pov *pov)
{
	pov->fov = 0.6 * PI;
	pov->pos.x = cube->player_x + 0.5;
	pov->pos.y = cube->player_y + 0.5;
	pov->facing = calc_facing(cube->map[cube->player_y][ cube->player_x]);
}

bool	check_if_hit(t_axis ray, rad angle, char **map)
{
	//printf("checking x: %f, y: %f with angle: %fPi\n", ray.x, ray.y, angle / PI);
	if (ray.x >= XMAPRES || ray.y >= YMAPRES || ray.x <= 0 || ray.y <= 0)
		return (1);
	// printf("data found: %c\n", map[(int)ray.y][(int)ray.x]);
	if (ft_fmod(ray.x, 0) <= ft_fmod(ray.y, 0) && (angle < 0.5 * PI || angle > 1.5 * PI)
		&& map[(int)ray.y][(int)ray.x] == '1')
		return (1);
	if (ft_fmod(ray.x, 0) <= ft_fmod(ray.y, 0) && (angle >= 0.5 * PI && angle <= 1.5 * PI)
		&& map[(int)ray.y][(int)ray.x - 1] == '1')
		return (1);
	if (ft_fmod(ray.y, 0) <= ft_fmod(ray.x, 0) && (angle < PI)
		&& map[(int)ray.y][(int)ray.x] == '1')
		return (1);
	if (ft_fmod(ray.y, 0) <= ft_fmod(ray.x, 0) && (angle >= PI)
		&& map[(int)ray.y - 1][(int)ray.x] == '1')
		return (1);
	return (0);
}

t_axis	x_raycast(t_axis d, t_axis stdd, t_axis pos, rad angle, char **map)
{
	t_axis	ray;

	// printf("x raycaster before d: x:%f, y:%f\n", pos.x, pos.y);
	ray.x = pos.x + d.x;
	ray.y = pos.y + (tan(angle) * d.x);
	// printf("x raycaster\n");
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
	// printf("y raycaster\n");
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

	// printf("checking angle for d and stdd: %fPi\n", angle / PI);
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
	// printf("dx: %f, dy: %f, stddx: %f, stddy: %f\n", d.x, d.y, stdd.x, stdd.y);
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
	linelen = linelen / 20;
	linelen = (linelen - 1) * -1;
	return (linelen);
}

void	fill_col(t_cube *cube, t_pov *pov, int i, t_axis ray, rad rayangle)
{
	float	linelen;
	float	valscale;
	int		j;

	// fill = cos((0.5 * PI) + (pov->rayangle - pov->facing)) * sqrt(pow(ray.y - pov->pos.y, 2) + pow(ray.x - pov->pos.x, 2));
	linelen = sqrt(pow(ray.y - pov->pos.y, 2) + pow(ray.x - pov->pos.x, 2));
	// printf("final line length: %f\n", linelen);
	//linelen = sin(0.5 * PI + (rayangle - pov->facing)) * linelen;
	// printf("0.5 * PI + (rayangle - pov->facing): %fPi\n", 0.5 * PI + (rayangle - pov->facing) / PI);
	valscale = (linelen / sqrt(25 + 144)) * (0.5 * SCREEN_Y);
	// printf("final line length: %f\n", linelen);
	j = 0.5 * SCREEN_Y;
	while (j > valscale && j > 0)
	{
		mlx_put_pixel(cube->g_img_DEMO, i, j, 0x444400FF);
		mlx_put_pixel(cube->g_img_DEMO, i, (SCREEN_Y - j), 0x444400FF);
		// if (j < valscale)
		// else
		// 	mlx_put_pixel(cube->g_img_DEMO, i, j, 0x004444FF);
		j--;
	}
	(void) rayangle;
}

char	find_wall_ori(t_axis ray, char **map, rad angle)
{
	// printf("\n\nTESR\n\n");
	if (ray.x >= XMAPRES || ray.y >= YMAPRES || ray.x < 0 || ray.y < 0)
		return (0);
	// printf("DEBUG: fmod x %f, y %f\n", ft_fmod(ray.x, 0), ft_fmod(ray.y, 0));
	// printf("DEBUG: wall = %c\n", map[(int)ray.y][(int)ray.x]);
	// printf("DEBUG: wall = %c\n", map[(int)ray.y - 1][(int)ray.x]);

	if (ft_fmod(ray.x, 0) <= ft_fmod(ray.y, 0) && (angle < 0.5 * PI || angle > 1.5 * PI)
			&& map[(int)ray.y][(int)ray.x] == '1')
		return ('W');
	if (ft_fmod(ray.x, 0) <= ft_fmod(ray.y, 0) && (angle >= 0.5 * PI && angle <= 1.5 * PI)
			&& map[(int)ray.y][(int)ray.x - 1] == '1')
		return ('E');
	if (ft_fmod(ray.y, 0) <= ft_fmod(ray.x, 0) && (angle < PI)
			&& map[(int)ray.y][(int)ray.x] == '1')
		return ('S');
	if (ft_fmod(ray.y, 0) <= ft_fmod(ray.x, 0) && (angle >= PI)
			&& map[(int)ray.y - 1][(int)ray.x] == '1')
		return ('N');
	// if(ft_fmod(ray.y, 0) <= ft_fmod(ray.x, 0))
	// 	printf("DEBUG IF1\n");
	// if((angle >= PI))
	// 	printf("DEBUG IF2\n");
	// if(map[(int)ray.y - 1][(int)ray.x] == '1')
	// 	printf("DEBUG IF3\n");
	// printf("DEBUG: ANGLE %f\n", angle);
	// printf("\n\nDEBUG: TEST WALL_ORI\n\n");
	return (0);
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
		printf("\nplayer position: x:%f, y:%f, facing: %fPi\n", pov->pos.x, pov->pos.y, round_rad(pov->facing) / PI);
	while (i < SCREEN_X)
	{
		// printf("\ncasting ray with angle: %fPi, column: %d, player position: x:%f, y:%f\n", rayangle / PI, i, pov->pos.x, pov->pos.y);
		pov->rays->end_pos = find_wall(map, pov, round_rad(rayangle));
		pov->rays->wall_ori = find_wall_ori(pov->rays->end_pos, map, round_rad(rayangle));
		// printf("found wall on x:%f, y:%f, ori_wall %c\n", pov->rays->end_pos.x, pov->rays->end_pos.y, pov->rays->wall_ori);
		scale = calc_scale_vert_line(pov, pov->rays);
		print_line(cube, pov->rays, scale, i);
		//fill_col(cube, pov, i, pov->rays->end_pos, rayangle);
		rayangle += anglestep;
		pov->rays++;
		i++;
	}
}

// int main()
// {
// 	char*	map[] = {	"111111111111",
// 						"100000000001",
// 						"100000N00001",
// 						"100000000001",
// 						"111111111111"};
// 	char**	res = malloc((sizeof(char*) * (YRES + 1)));
// 	res[YRES] = NULL;
// 	for (int i = 0; i < YRES; i++)
// 	{
// 		res[i] = malloc (sizeof(char) * (XRES + 1));
// 		res[i][XRES] = '\0';
// 	}
// 	t_pov pov = find_playpos(map);
// 	cast_rays(map, pov, res);
// 	printf("position: x:%f, y:%f\n", pov->pos.x, pov->pos.y);
// }




		// axis = starting_axis(pov->rayx, pov->rayy, pov->rayangle);
		// if (axis == X)
		// {
		// 	if (angle > PI)
		// 		pov->rayy -= tan(angle) * ft_fmod(pov->rayx, 1);
		// 	else
		// 		pov->rayy += tan(angle) * ft_fmod(pov->rayx, 1);
		// 	if (angle > 0.5 * PI && angle < 1.5 * PI)
		// 		pov->rayx -= ft_fmod(pov->rayx, 1);
		// 	else
		// 		pov->rayx += 1 - ft_fmod(pov->rayx, 0);
		// }
		// else if (axis == Y)
		// {
		// 	if (angle > 0.5 * PI && angle < 1.5 * PI)
		// 		pov->rayx -= ft_fmod(pov->rayy, 1) / tan(angle);
		// 	else
		// 		pov->rayx += ft_fmod(pov->rayy, 1) / tan(angle);
		// 	if (angle > PI)
		// 		pov->rayy -= ft_fmod(pov->rayy, 1);
		// 	else
		// 		pov->rayy += 1 - ft_fmod(pov->rayy, 0);
		// }
		// else
		// {
		// 	if (angle > 0.5 * PI && angle < 1.5 * PI)
		// 		pov->rayx -= ft_fmod(pov->rayy, 1);
		// 	else
		// 		pov->rayx += 1 - ft_fmod(pov->rayy, 0);
		// }
// bool	starting_axis(float x, float y, float angle)
// {
// 	float	urrad;
// 	float	drrad;
// 	float	ulrad;
// 	float	dlrad;

// 	urrad = round_rad(atan((-1 * ft_fmod(y, 0)) / (1 - ft_fmod(x, 0))));
// 	drrad = round_rad(atan((1 - ft_fmod(y, 0)) / (1 - ft_fmod(x, 0))));
// 	ulrad = round_rad(atan((-1 * ft_fmod(y, 0)) / (-1 * ft_fmod(x, 0))));
// 	dlrad = round_rad(atan((1 - ft_fmod(y, 0)) / (-1 * ft_fmod(x, 0))));
// 	// urrad = atan((-1 * ft_fmod(y)) / (1 - ft_fmod(x)));
// 	// drrad = atan((1 - ft_fmod(y)) / (1 - ft_fmod(x)));
// 	// ulrad = atan((-1 * ft_fmod(y)) / (-1 * ft_fmod(x)));
// 	// dlrad = atan((1 - ft_fmod(y)) / (-1 * ft_fmod(x)));
// 	ulrad = ulrad + 2 * ((0.75 * PI) - ulrad);
// 	dlrad = dlrad - 2 * (dlrad - (1.25 * PI));
// 	printf("urrad check: %f, ulrad check: %f, dlrad check: %f, drrad check: %f\n", tan(urrad) * 1 - ft_fmod(x, 1), tan(ulrad) * ft_fmod(x, 0), tan(dlrad) * ft_fmod(x, 0), tan(urrad) * 1 - ft_fmod(x, 1));
// 	printf("up right: %fPi, down right: %fPi, up left: %fPi, down left: %fPi.\n", urrad / PI, drrad / PI, ulrad / PI, dlrad / PI);
// 	if ((angle > urrad && angle < drrad)
// 		|| (angle > dlrad && angle < ulrad))
// 		return (X);
// 	else if ((angle < urrad && angle > ulrad)
// 			|| (angle < dlrad && angle > drrad))
// 		return (Y);
// 	printf("It's a junc.\n");
// 	return (JUNC);
// }



// if (angle > 0.5 * PI && angle < 1.5 * PI)
// 	{
// 		d.y = tan(angle) * -ft_fmod(pos.x, 0);
// 		stdd.y = -tan(angle);
// 	}
// 	else
// 	{
// 		d.y = tan(angle) * (1 - ft_fmod(pos.x, 0));
// 		stdd.y = tan(angle);
// 	}
// 	if (angle > 0 && angle < PI)
// 	{
// 		d.x = tan(angle) * 1 - ft_fmod(pos.y, 0);
// 		stdd.x = 1 / tan(angle);
// 	}
// 	else
// 	{
// 		d.x = tan(angle) * -ft_fmod(pos.y, 0);
// 		stdd.x = -1 / tan(angle);
// 	}

// t_axis	x_raycast(t_axis d, t_axis stdd, t_axis pos, rad angle, char **map)
// {
// 	t_axis	ray;

// 	printf("x raycaster before d: x:%f, y:%f\n", pos.x, pos.y);
// 	ray.x = pos.x + d.x;
// 	ray.y = pos.y + (tan(angle) * d.x);
// 	printf("x raycaster\n");
// 	while (!check_if_hit(ray, angle, map))
// 	{
// 		ray.y += tan(angle) * stdd.x;
// 		ray.x += stdd.x;
// 	}
// 	return (ray);
// }

// t_axis	y_raycast(t_axis d, t_axis stdd, t_axis pos, rad angle, char **map)
// {
// 	t_axis	ray;

// 	ray.y = pos.y + d.y;
// 	ray.x = pos.x + (d.y / tan(angle));
// 	printf("y raycaster\n");
// 	while (!check_if_hit(ray, angle, map))
// 	{
// 		ray.x += stdd.y / tan(angle);
// 		ray.y += stdd.y;
// 	}
// 	return (ray);
// }
