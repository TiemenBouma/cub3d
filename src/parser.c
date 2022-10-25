#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <fcntl.h>
#include "../includes/get_next_line/get_next_line.h"
#define ELEMENTS_COUNT 6

#include <stdio.h>

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

int validate_file_name(t_file *file)
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

int	set_rgb(char *str, int rgb[])
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	while (split[i])
		i++;
	if (i != 3)
		error_msg_exit("Error: Wrong RGB Color code.\n", 1);
	rgb[0] = ft_atoi(split[0]);
	rgb[1] = ft_atoi(split[1]);
	rgb[2] = ft_atoi(split[2]);
	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			error_msg_exit("Error: Wrong RGB Color code.\n", 1);
		i++;
	}
	return (0);
}

int	parse_elements(t_cube *cube, t_file *file)
{
	int	i;
	char	*line;
	char	**split;

	i = 0;
	while (i < ELEMENTS_COUNT)
	{
		line = get_line(file);
		file->start_line_map++;
		if (line == NULL)
			error_msg_exit("Error: Initialisation file not correct.\n", 1);
		if (line[0] == '\0')
			continue ;
		split = ft_split(line, ' ');
		if (split == NULL)
			exit (1);
		else if (split[0] == NULL)
			continue ;
		else if (split[1] == NULL)
			error_msg_exit("Error: no valid Element.\n", 1);
		else if (ft_strncmp(split[0], "NO", 3) == 0)
			cube->no = ft_strdup(split[1]);
		else if (ft_strncmp(split[0], "EA", 3) == 0)
			cube->ea = ft_strdup(split[1]);
		else if (ft_strncmp(split[0], "SO", 3) == 0)
			cube->so = ft_strdup(split[1]);
		else if (ft_strncmp(split[0], "WE", 3) == 0)
			cube->we = ft_strdup(split[1]);
		else if (ft_strncmp(split[0], "F", 2) == 0)
			set_rgb(split[1], cube->floor_rgb);
		else if (ft_strncmp(split[0], "C", 2) == 0)
			set_rgb(split[1], cube->ceilling_rgb);
		else
			error_msg_exit("Error: No element found.\n", 1);
		i++;
	}
	//check if all elements are used
	return (0);
}

int	parse_cub_file_lines(t_cube *cube, t_file *file)
{
	parse_elements(cube, file);
	parse_map_element(cube, file);
	return (0);
}

int	parsing(t_cube *cube, t_file *file)
{

	validate_file_name(file);
	open_cub_file(file);
	// printf("DEBUG:player count parsing %d\n", cube->player_count);
	parse_cub_file_lines(cube, file);
	return 0;
}