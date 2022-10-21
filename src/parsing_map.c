#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include "../includes/get_next_line/get_next_line.h"
#include <unistd.h>

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

int	calculate_map_length(t_cube *cube, t_file *file, char *line)
{
	int		temp_width;
	// printf("DEBUG: mpa length BEGIN: %d\n", cube->map_length);
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
		// printf("DEBUG: mpa length: %d\n", cube->map_length);
		free(line);
		line = get_line(file);
	}
	if (cube->map_width < 3 || cube->map_length < 3)
		error_msg_exit("Error: Map lenths not correct.\n", 1);
	return (0);
}

void map_malloc(t_cube *cube, char ***map)
{
	int i;

	i = 0;
	*map = malloc(sizeof(char *) * (cube->map_length + 3));
	if (*map == NULL)
		error_msg_exit("Error: Malloc error", 1);
	(*map)[cube->map_length + 2] = NULL;
	while (i < cube->map_length + 3)
	{
		(*map)[i] = ft_calloc(cube->map_width + 3, sizeof(char));
		if ((*map)[i] == NULL)
			error_msg_exit("Error: Malloc error", 1);
		//(*map)[i][cube->map_width] = '\0';
		i++;
	}
}

// void map_malloc(t_cube *cube)
// {
// 	int i;

// 	i = 0;
// 	cube->map = malloc(sizeof(char *) * (cube->map_length + 1));
// 	if (cube->map == NULL)
// 		error_msg_exit("Error: Malloc error", 1);
// 	cube->map[cube->map_length] = NULL;
// 	while (i < cube->map_length)
// 	{
// 		cube->map[i] = ft_calloc(cube->map_width + 1, sizeof(char));
// 		if (cube->map[i] == NULL)
// 			error_msg_exit("Error: Malloc error", 1);
// 		//(*map)[i][cube->map_width] = '\0';
// 		i++;
// 	}
// }

void	set_map_array(t_cube *cube, t_file *file)
{
	int	i;
	char	*line;

	i = 0;
	//map_malloc(cube);
	map_malloc(cube, &cube->map);
	map_malloc(cube, &cube->cpy_map);
	while (i < file->start_line_map - 1)
	{
		line = get_next_line(file->file_fd);
		free(line);
		i++;
	}
	i = 1;
	

	while (i < cube->map_length + 1)
	{
		line = get_line(file);
		ft_memcpy(cube->map[i] + 1, line, ft_strlen(line));
		ft_memcpy(cube->cpy_map[i] + 1, line, ft_strlen(line));
		// printf("memcpy = %s\n", cube->cpy_map[i] + 1);
		i++;
	}
		//printf("DEBUG\n");
}

// void printmap(t_cube *cube)
// {
// 	int i;

// 	i = 0;
// 	while (i < cube->map_length)
// 	{
// 		printf("%s\n", cube->cpy_map[i]);
// 		i++;
// 	}
// }

int	parse_map_element(t_cube *cube, t_file *file)
{
	char	*line;

	line = empty_line_read(file);
	calculate_map_length(cube, file, line);
	close(file->file_fd);
	open_cub_file(file);

	set_map_array(cube, file);

	validate_map(cube->cpy_map);
	//printmap(cube);

	return 0;
}