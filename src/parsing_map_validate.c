#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"

#include <stdio.h>

int	recursive_map_check(t_cube *cube, int x, int y);

void	start_location(char **map, int *cordinates)
{
	int y;
	int	x;

	y = 0;
	
	while (map[y])
	{
		x = 1;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				cordinates[0] = y;
				cordinates[1] = x;
				return ;
				// break ;
			}
			x++;
		}
		// if (map[y][x] == '0')
		// 	break ;
		y++;
	}
	cordinates[0] = y;
	cordinates[1] = x;
}


void check_tile(t_cube *cube, int x, int y)
{
	if (cube->cpy_map[y][x] == '\0')
	{
	//	printf("DEBUG: RECUR1\n\n");
		error_msg_exit("Error:  Invalid map.\n", 1);
	}
	if (cube->cpy_map[y][x] == '0')
	{
		cube->cpy_map[y][x] = '1';
		//printf("DEBUG: RECUR2\n\n");
		recursive_map_check(cube, x, y);
	}
	if (cube->cpy_map[y][x] == '1')
	{
	//	printf("DEBUG: RECUR3\n\n");
		return ;
	}
	if (cube->cpy_map[y][x] == 'N' || cube->cpy_map[y][x] == 'E' || cube->cpy_map[y][x] == 'S' || cube->cpy_map[y][x] == 'W')
	{
		cube->player_count++;
					//printf("DEBUG: x = %d, y = %d\n", cube->player_x, cube->player_y);
		// cube->player_x = x;
		// cube->player_y = y;
		// 			printf("DEBUG: x = %d, y = %d\n", cube->player_x, cube->player_y);
		cube->cpy_map[y][x] = '1';
		//printf("DEBUG: RECUR4\n\n");
		recursive_map_check(cube, x, y);
	}
}

int	recursive_map_check(t_cube *cube, int x, int y)
{
	//cube->cpy_map[y][x] = '1';
	check_tile(cube, x, y - 1);
	check_tile(cube, x, y + 1);
	check_tile(cube, x - 1, y);
	check_tile(cube, x + 1, y);
	return (0);
}

void validate_map(t_cube *cube)
{
	//int	cordinates[2];

	//start_location(cube->cpy_map, cordinates);
	//printf("DEBUG cor x = %d y = %d\n\n", cordinates[1], cordinates[0]);
	//printmap(cube->cpy_map);
	recursive_map_check(cube, cube->player_x, cube->player_y);
	if (cube->player_count != 1)
	{
		error_msg_exit("Error: Wrong player count.\n", 1);
	}
	//printmap(cube->cpy_map);
}