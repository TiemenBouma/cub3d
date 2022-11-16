#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdio.h>

int	recursive_map_check(t_cube *cube, int x, int y);

void	check_tile(t_cube *cube, int x, int y)
{
	if (cube->cpy_map[y][x] == '\0')
		error_msg_exit("Error:  Invalid map.\n", 1);
	if (cube->cpy_map[y][x] == '0')
	{
		cube->cpy_map[y][x] = '1';
		recursive_map_check(cube, x, y);
	}
	if (cube->cpy_map[y][x] == '1')
		return ;
	if (cube->cpy_map[y][x] == 'N' || cube->cpy_map[y][x] == 'E'
		|| cube->cpy_map[y][x] == 'S' || cube->cpy_map[y][x] == 'W')
	{
		cube->player_count++;
		cube->cpy_map[y][x] = '1';
		recursive_map_check(cube, x, y);
	}
}

int	recursive_map_check(t_cube *cube, int x, int y)
{
	check_tile(cube, x, y - 1);
	check_tile(cube, x, y + 1);
	check_tile(cube, x - 1, y);
	check_tile(cube, x + 1, y);
	return (0);
}

void	validate_map(t_cube *cube)
{
	recursive_map_check(cube, cube->player_x, cube->player_y);
	if (cube->player_count != 1)
		error_msg_exit("Error: Wrong player count.\n", 1);
}
