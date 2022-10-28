#include "includes/cub3d.h"

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

// bool	check_if_hit(t_axis ray, float angle, char **map)
// {
// 	printf("checking x: %f, y: %f with angle: %fPi\n", ray.x, ray.y, angle / PI);
// 	if (ray.x >= XMAPRES || ray.y >= YMAPRES || ray.x < 0 || ray.y < 0)
// 		return (1);
// 	// printf("data found: %c\n", map[(int)ray.y][(int)ray.x]);
// 	if (ft_fmod(ray.x, 0) <= ft_fmod(ray.y, 0) && (angle < 0.5 * PI || angle > 1.5 * PI)
// 		&& map[(int)ray.y][(int)ray.x] == '1')
// 		return (1);
// 	if (ft_fmod(ray.x, 0) <= ft_fmod(ray.y, 0) && (angle >= 0.5 * PI && angle <= 1.5 * PI)
// 		&& map[(int)ray.y][(int)ray.x - 1] == '1')
// 		return (1);
// 	if (ft_fmod(ray.y, 0) <= ft_fmod(ray.x, 0) && (angle < PI)
// 		&& map[(int)ray.y][(int)ray.x] == '1')
// 		return (1);
// 	if (ft_fmod(ray.x, 0) <= ft_fmod(ray.x, 0) && (angle >= PI)
// 		&& map[(int)ray.y - 1][(int)ray.x] == '1')
// 		return (1);
// 	return (0);
// }
