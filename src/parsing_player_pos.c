#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>
#include <stdbool.h>

static double	calc_facing(char player)
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
	pov->fov = PI * (0.6 * (double)(cube->window_x / 1024));
	pov->pos.x = cube->player_x + 0.5;
	pov->pos.y = cube->player_y + 0.5;
	pov->facing = calc_facing(cube->map[cube->player_y][ cube->player_x]);
}