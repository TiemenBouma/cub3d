#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"

#include <stdio.h>

int	recursive_map_check(char **map, int x, int y);

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


void check_tile(char **map, int x, int y)
{
	if (map[y][x] == '\0')
		error_msg_exit("Error:  Invalid map.\n", 1);
	if (map[y][x] == '0')
		recursive_map_check(map, x, y);
	if (map[y][x] == '1')
		return ;
	if (map[y][x] == 'N')
		recursive_map_check(map, x, y);
	if (map[y][x] == 'E')
		recursive_map_check(map, x, y);
	if (map[y][x] == 'S')
		recursive_map_check(map, x, y);
	if (map[y][x] == 'W')
		recursive_map_check(map, x, y);
}

int	recursive_map_check(char **map, int x, int y)
{
	printf("DEBUG x = %d, y = %d\n", x, y);
	map[x][y] = '1';
	check_tile(map, x, y - 1);
	check_tile(map, x, y + 1);
	check_tile(map, x - 1, y);
	check_tile(map, x + 1, y);
	return (0);
}

void validate_map(char **map)
{
	int	cordinates[2];

	start_location(map, cordinates);
	recursive_map_check(map, cordinates[1], cordinates[0]);
	

}