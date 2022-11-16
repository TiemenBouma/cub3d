#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include "../includes/get_next_line/get_next_line.h"
#include <unistd.h>

#include <stdio.h>

char	*empty_line_read(t_file *file)
{
	int		i;
	char	*line;

	i = 0;
	while (i < INT_MAX)
	{
		line = get_line(file);
		file->start_line_map++;
		if (line == NULL)
			error_msg_exit("Error: No map in file.\n", 1);
		if (line[0] == '\0')
		{
			i++;
			free(line);
		}
		else
			break ;
	}
	return (line);
}

int	calculate_map_length(t_cube *cube, t_file *file, char *line)
{
	int		temp_width;

	while (1)
	{
		if (line == NULL)
			break ;
		if (line[0] == '\0')
			break ;
		temp_width = ft_strlen(line);
		if (temp_width > cube->map_width)
			cube->map_width = temp_width;
		cube->map_length++;
		free(line);
		line = get_line(file);
	}
	if (cube->map_width < 3 || cube->map_length < 3)
		error_msg_exit("Error: Map lenths not correct.\n", 1);
	free(line);
	return (0);
}

void	map_malloc(t_cube *cube, char ***map)
{
	int	i;

	i = 0;
	*map = ft_calloc(cube->map_length + 3, sizeof(char *));
	if (*map == NULL)
		error_msg_exit("Error: Malloc error", 1);
	(*map)[cube->map_length + 2] = NULL;
	while (i < cube->map_length + 2)
	{
		(*map)[i] = ft_calloc(cube->map_width + 2, sizeof(char));
		if ((*map)[i] == NULL)
			error_msg_exit("Error: Malloc error", 1);
		i++;
	}
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
