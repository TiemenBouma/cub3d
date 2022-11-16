#include <fcntl.h>
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"

int	open_cub_file(t_file *file)
{
	file->file_fd = open(file->file_name, O_RDONLY);
	if (file->file_fd < 0)
	{
		ft_putstr_fd("Error: Open .cub file failed.\n", 1);
		exit(1);
	}
	return (0);
}

int	validate_file_name(t_file *file)
{
	int	len;

	len = ft_strlen(file->file_name);
	if (len < 5)
	{
		ft_putstr_fd("Error: Wrong .cub filename.\n", 2);
		exit (1);
	}
	if (file->file_name[len - 1] != 'b' || file->file_name[len - 2] != 'u'
		|| file->file_name[len - 3] != 'c' || file->file_name[len - 4] != '.')
	{
		ft_putstr_fd("Error: File needs .cub extention.\n", 2);
		exit (1);
	}
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

char	*empty_line_read_map(t_file *file)
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