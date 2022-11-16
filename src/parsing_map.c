#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include "../includes/get_next_line/get_next_line.h"
#include <unistd.h>

#include <stdio.h>

int	calculate_map_length(t_cube *cube, t_file *file, char *line)
{
	int	temp_width;

	while (1)
	{
		if (line == NULL)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		temp_width = ft_strlen(line);
		if (temp_width > cube->map_width)
			cube->map_width = temp_width;
		cube->map_length++;
		free(line);
		line = get_line(file);
	}
	if (cube->map_width < 3 || cube->map_length < 3)
		error_msg_exit("Error: Map lenths not correct.\n", 1);
	return (0);
}

int	is_player(char *line)
{
	if (ft_strchr(line, 'N'))
		return (ft_strchr(line, 'N') - line);
	else if (ft_strchr(line, 'E'))
		return (ft_strchr(line, 'E') - line);
	else if (ft_strchr(line, 'S'))
		return (ft_strchr(line, 'S') - line);
	else if (ft_strchr(line, 'W'))
		return (ft_strchr(line, 'W') - line);
	return (-1);
}

char	*set_map_array2(t_cube *cube, t_file *file)
{
	int 	i;
	char	*line;

	i = 0;
	map_malloc(cube, &cube->map);
	map_malloc(cube, &cube->cpy_map);
	while (i < file->start_line_map - 1)
	{
		line = get_next_line(file->file_fd);
		free(line);
		i++;
	}
	return (line);
}

void	set_map_array(t_cube *cube, t_file *file)
{
	int		i;
	char	*line;

	line = set_map_array2(cube, file);
	i = 1;
	while (i < cube->map_length + 1)
	{
		line = get_line(file);
		if (is_player(line) > 0)
		{
			cube->player_x = is_player(line) + 1;
			cube->player_y = i;
			cube->has_player = 1;
		}
		ft_memcpy(cube->map[i] + 1, line, ft_strlen(line));
		ft_memcpy(cube->cpy_map[i] + 1, line, ft_strlen(line));
		free(line);
		i++;
	}
	if (cube->has_player == 0)
		error_msg_exit("Error: No player found.\n", 1);
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
	return 0;
}