#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>

bool	check_if_hit(t_cube *cube, t_axis ray, rad angle, char **map)
{
	//printf("checking x: %f, y: %f with angle: %fPi\n", ray.x, ray.y, angle / PI);
	if (ray.x >= cube->map_width || ray.y >= cube->map_length || ray.x <= 0 || ray.y <= 0)
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

char	find_wall_ori(t_cube *cube, t_axis ray, char **map, rad angle)
{
	if (ray.x >= cube->map_width || ray.y >= cube->map_length || ray.x < 0 || ray.y < 0)
	{
		printf("DEBUG: ray out of bounds\n");
		printf("DEBUG: STATS: ray.x %f, cube->width %d, ray.y %f, cube->y %d\n", ray.x, cube->map_width, ray.y, cube->map_length);
		return (0);
	}
	// printf("DEBUG: fmod x %f, y %f\n", ft_fmod(ray.x, 0), ft_fmod(ray.y, 0));
	// printf("DEBUG: wall = %c\n", map[(int)ray.y][(int)ray.x]);
	// printf("DEBUG: wall = %c\n", map[(int)ray.y - 1][(int)ray.x]);

	if (ft_fmod(ray.x, 0) <= ft_fmod(ray.y, 0) && (angle < 0.5 * PI || angle > 1.5 * PI)
			&& map[(int)ray.y][(int)ray.x] == '1')
		return ('W');
	else if (ft_fmod(ray.x, 0) <= ft_fmod(ray.y, 0) && (angle >= 0.5 * PI && angle <= 1.5 * PI)
			&& map[(int)ray.y][(int)ray.x - 1] == '1')
		return ('E');
	else if (ft_fmod(ray.y, 0) <= ft_fmod(ray.x, 0) && (angle < PI)
			&& map[(int)ray.y][(int)ray.x] == '1')
		return ('S');
	else if (ft_fmod(ray.y, 0) <= ft_fmod(ray.x, 0) && (angle >= PI)
			&& map[(int)ray.y - 1][(int)ray.x] == '1')
		return ('N');
	else
	{
		printf("DEBUG: no wall found\n");
		return (0);
	}
}


	// if(ft_fmod(ray.y, 0) <= ft_fmod(ray.x, 0))
	// 	printf("DEBUG IF1\n");
	// if((angle >= PI))
	// 	printf("DEBUG IF2\n");
	// if(map[(int)ray.y - 1][(int)ray.x] == '1')
	// 	printf("DEBUG IF3\n");
	// printf("DEBUG: ANGLE %f\n", angle);
	//printf("\n\nDEBUG: TEST WALL_ORI\n\n");

