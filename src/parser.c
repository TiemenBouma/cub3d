#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <fcntl.h>
#include "../includes/get_next_line/get_next_line.h"
#define ELEMENTS_COUNT 6

#include <stdio.h>

// int	validate_file_content()
// {

// 	return (0);
// }

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

char	*get_line(t_file *file)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	line = get_next_line(file->file_fd);
	while (line[i] != '\0'  && line[i] != '\n')
		i++;
	temp = ft_substr(line, 0, i);
	free(line);
	line = temp;
	return (line);
}

int	set_rgb(char *str, int rgb[])
{
	char	**split;

	split = ft_split(str, ',');
	rgb[0] = ft_atoi(split[0])
	rgb[1] = ft_atoi(split[1])
	rgb[2] = ft_atoi(split[2])
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
		if (line[0] == '\0')
			continue ;
		split = ft_split(line, ' ');
		printf("DEBUG split %s\n %s\n", split[0], split[1]);
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
		{
			set_rgb(split[1], cube->floor_rgb);
			// cube->floor_rgb[0] = 66;
			// cube->floor_rgb[1] = 135;
			// cube->floor_rgb[2] = 245;
		}
		else if (ft_strncmp(split[0], "C", 2) == 0)
		{
			set_rgb(split[1], cube->ceilling_rgb);
			// cube->ceilling_rgb[0] = 80;
			// cube->ceilling_rgb[1] = 230;
			// cube->ceilling_rgb[2] = 125;
		}
		else
			error_msg_exit("Error: No element found.\n", 1);
		i++;
	}
	//check if all elements are used
	return (0);
}

// int	parse_map_element(t_cube *cube, t_file *file)
// {

// }

int	parse_cub_file_lines(t_cube *cube, t_file *file)
{
	parse_elements(cube, file);
	//parse_map_element(cube, file);
	return (0);
}

int	parsing(t_cube *cube, t_file *file)
{
	//char	*line;
	//char	*temp;
	int i;
	i = 0;

	validate_file_name(file);
	open_cub_file(file);

	parse_cub_file_lines(cube, file);
	// //gnl
	// line = get_next_line(file->file_fd);
	// printf("DEBUG: LINE = |%s|\n", line);

	// while (line[i] != '\0'  && line[i] != '\n')
	// 	i++;
	// temp = ft_substr(line, 5, i - 5);
	// free(line);
	// line = temp;
	// printf("DEBUG: LINE = %s\n", line);
	// cube->no = ft_strdup(line);
	// printf("DEBUG2\n");
	// free(line);

	// cube->ea = ft_strdup("greystone.png");
	// cube->so = ft_strdup("greystone.png");
	// cube->we = ft_strdup("greystone.png");
	return 0;
}