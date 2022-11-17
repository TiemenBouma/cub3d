/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_map_validate.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 10:41:19 by tiemen        #+#    #+#                 */
/*   Updated: 2022/11/17 13:32:59 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	recursive_map_check(t_cube *cube, int x, int y);

int	is_valid_char(char mapchar)
{
	if (mapchar == 'N'
		|| mapchar == 'S'
		|| mapchar == 'E'
		|| mapchar == 'W'
		|| mapchar == '1'
		|| mapchar == '0')
		return (1);
	return (0);
}

void	check_tile(t_cube *cube, int x, int y)
{
	if (is_valid_char(cube->cpy_map[y][x]) == 0)
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
