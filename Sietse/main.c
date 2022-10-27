#include "includes/cub3d.h"

float	round_rad(float rad)
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

t_pov	find_playpos(char** map)
{
	int			i;
	int			j;
	t_pov		ret;

	i = 0;
	ret.facing = 0.5 * PI;
	ret.fov = 0.4 * PI;
	ret.rayangle = ret.facing - (0.5 * ret.fov);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				ret.pos.x = j + 0.5;
				ret.pos.y = i + 0.5;
				return (ret);
			}
			j++;
		}
		i++;
	}
	return (ret);
}

bool	check_if_hit(t_axis ray, float angle, char **map)
{
	printf("checking x: %f, y: %f with angle: %fPi\n", ray.x, ray.y, angle / PI);
	if (ray.x >= XMAPRES || ray.y >= YMAPRES || ray.x < 0 || ray.y < 0)
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

t_axis	x_raycast(t_axis d, t_axis stdd, t_axis pos, float angle, char **map)
{
	t_axis	ray;

	ray.x = pos.x + d.x;
	ray.y = pos.y + tan(angle) * d.x;
	printf("x raycaster\n");
	while (!check_if_hit(ray, angle, map))
	{
		ray.y = tan(angle) * stdd.x;
		ray.x += stdd.x;
	}
	return (ray);
}

t_axis	y_raycast(t_axis d, t_axis stdd, t_axis pos, float angle, char **map)
{
	t_axis	ray;

	ray.y = pos.y + d.y;
	ray.x = pos.x + d.y / tan(angle);
	printf("y raycaster\n");
	while (!check_if_hit(ray, angle, map))
	{
		ray.x = stdd.y / tan(angle);
		ray.y += stdd.y;
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

t_axis	find_wall(char **map, t_axis pos, float	angle)
{
	t_axis	d;
	t_axis	stdd;
	t_axis	xraycast;
	t_axis	yraycast;

	printf("checking angle for d and stdd: %fPi\n", angle / PI);
	if (angle > 0.5 * PI && angle < 1.5 * PI)
	{
		d.y = tan(angle) * -ft_fmod(pos.x, 0);
		stdd.y = -tan(angle);
	}
	else
	{
		d.y = tan(angle) * (1 - ft_fmod(pos.x, 0));
		stdd.y = tan(angle);
	}
	if (angle > 0 && angle < PI)
	{
		d.x = tan(angle) * 1 - ft_fmod(pos.y, 0);
		stdd.x = 1 / tan(angle);
	}
	else
	{
		d.x = tan(angle) * -ft_fmod(pos.y, 0);
		stdd.x = -1 / tan(angle);
	}
	printf("dx: %f, dy: %f, stddx: %f, stddy: %f\n", d.x, d.y, stdd.x, stdd.y);
	xraycast = x_raycast(d, stdd, pos, angle, map);
	yraycast = y_raycast(d, stdd, pos, angle, map);
	if (cmp_rays(xraycast, yraycast, pos) == X)
		return (xraycast);
	return (yraycast);
}

void	fill_col(t_pov pov, char **field, int i, t_axis ray)
{
	float	fill;
	float	valscale;
	int		j;

	// fill = cos((0.5 * PI) + (pov.rayangle - pov.facing)) * sqrt(pow(ray.y - pov.pos.y, 2) + pow(ray.x - pov.pos.x, 2));
	fill = sqrt(pow(ray.y - pov.pos.y, 2) + pow(ray.x - pov.pos.x, 2));
	valscale = (fill / sqrt(25 + 144)) * YRES;
	printf("fill: %f\n", fill);
	j = 0;
	while (j < YRES)
	{
		if (j < valscale)
			field[j][i] = '0';
		else
			field[j][i] = '1';
		j++;
	}
}

void	cast_rays(char **map, t_pov pov, char **field)
{
	float	anglestep;
	int		i;
	t_axis	ray;

	i = 0;
	anglestep = pov.fov / XRES;
	pov.ray.x = pov.pos.x;
	pov.ray.y = pov.pos.y;
	while (pov.rayangle < pov.facing + (0.5 * pov.fov))
	{
		printf("\ncasting ray with angle: %fPi, column %d\n", pov.rayangle / PI, i);
		ray = find_wall(map, pov.pos, round_rad(pov.rayangle));
		printf("found wall on x:%f, y:%f\n", ray.x, ray.y);
		fill_col(pov, field, i, ray);
		pov.rayangle += anglestep;
		i++;
	}
	print_field(field);
}

int main()
{
	char*	map[] = {	"111111111111",
						"100000000001",
						"100000P00001",
						"100000000001",
						"111111111111"};
	char**	res = malloc((sizeof(char*) * (YRES + 1)));
	res[YRES] = NULL;
	for (int i = 0; i < YRES; i++)
	{
		res[i] = malloc (sizeof(char) * (XRES + 1));
		res[i][XRES] = '\0';
	}
	t_pov pov = find_playpos(map);
	printf("position: x:%f, y:%f\n", pov.pos.x, pov.pos.y);
	cast_rays(map, pov, res);
}




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
// 		d.x = -ft_fmod(pos.x, 1);
// 		stdd.x = 1 / tan(angle);
// 	}
// 	else
// 	{
// 		d.x = 1 - ft_fmod(pos.x, 0);
// 		stdd.x = 1 / tan(angle);
// 	}
// 	if (angle > 0 && angle < PI)
// 	{
// 		d.y = -ft_fmod(pos.y, 1);
// 		stdd.y = tan(angle);
// 	}
// 	else
// 	{
// 		d.y = 1 - ft_fmod(pos.y, 0);
// 		stdd.y = tan(angle);
// 	}


