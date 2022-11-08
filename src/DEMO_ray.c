#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int ft_abs (int i)
{
  return i < 0 ? -i : i;
}

int fuc(t_pov *pov)
{
	double	pos_x = pov->pos.x;
	double	pos_y = pov->pos.y;
	double	dir_x = -1;
	double	dir_y = 0;
	double	plane_x = 0;
	double	plane_y = 0.66;
	int		x;
	int		w;

	double camera_x;
	double raydir_x;
	double raydir_y;
	int		map_x;
	int		map_y;
	double sidedist_x;
	double sidedist_y;
	double	delta_dist_x;
	double	delta_dist_y;

	double	perp_wall_dist;
	int step_x;
	int step_y;
	int hit;
	int wall_side;

	x = 0;
	w = SCREEN_X;
	while (1)
	{
		while (x < w)
		{
			camera_x = 2 * x / (double) w - 1;
			raydir_x = dir_x + plane_x * camera_x;
			raydir_y = dir_y + plane_y * camera_x;

			map_x = (int)pos_x;
			map_y = (int)pos_y;

			sidedist_x = 0;
			sidedist_y = 0;

			if (raydir_x == 0)
				delta_dist_x = 1e30;
			else
				delta_dist_x = ft_abs(1 / raydir_x);
			if (raydir_y == 0)
				delta_dist_y = 1e30;
			else
				delta_dist_y = ft_abs(1 / raydir_y);

			perp_wall_dist = 0;
			step_x = 0;
			step_y = 0;
			hit = 0;
			wall_side = 0;

			if ( raydir_x < 0)
			{
				step_x = -1;
				sidedist_x = (pos_x - map_x) * delta_dist_x;
			}
			else
			{
				step_x = 1;
				sidedist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
			}
			

			x++;
		}
	}

}