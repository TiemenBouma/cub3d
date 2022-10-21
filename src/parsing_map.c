#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"

#include <stdio.h>

char	*empty_line_read(t_file *file)
{
	int	i;
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

int	calculate_map_length(t_cube *cube, t_file *file)
{
	int		temp_width;
	char	*line;

	while (1)
	{
		printf("%s\n", line);
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
		error_msg_exit("Error: Map lenths not correct.\n");
	return (0);
}

int	parse_map_element(t_cube *cube, t_file *file)
{
	char	*line;

	line = empty_line_read(file);
	calculate_map_length(cube, file);
	close(file->file_fd);
	open_cub_file(file);

	return 0;
}