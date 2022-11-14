#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>

void	set_dir_vector(char ori, double *dir_x, double *dir_y)
{
	if (ori == 'N')
	{
		*dir_x = 0;
		*dir_y = -1;
	}
	else if (ori == 'E')
	{
		*dir_x = 1;
		*dir_y = 0;
	}
	else if (ori == 'S')
	{
		*dir_x = 0;
		*dir_y = 1;
	}
	else if (ori == 'W')
	{
		*dir_x = -1;
		*dir_y = 0;
	}
}

void	set_plane_vector(char ori, double *place_x, double *place_y)
{
	if (ori == 'N')
	{
		*place_x = -0.66;
		*place_y = 0;
	}
	else if (ori == 'E')
	{
		*place_x = 0;
		*place_y = -0.66;
	}
	else if (ori == 'S')
	{
		*place_x = 0.66;
		*place_y = 0;
	}
	else if (ori == 'W')
	{
		*place_x = 0;
		*place_y = 0.66;
	}
}