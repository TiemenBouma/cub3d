/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_map2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 10:41:26 by tiemen        #+#    #+#                 */
/*   Updated: 2022/11/17 11:07:47 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <unistd.h>

void	check_player(t_cube *cube, char *line, int i)
{
	if (is_player(line) > 0)
	{
		cube->player_x = is_player(line) + 1;
		cube->player_y = i;
	}
}

int	parse_map_element(t_cube *cube, t_file *file)
{
	char	*line;

	line = empty_line_read_map(file);
	calculate_map_length(cube, file, line);
	close(file->file_fd);
	open_cub_file(file);
	set_map_array(cube, file);
	cube->map_length++;
	cube->map_width++;
	validate_map(cube);
	return (0);
}
