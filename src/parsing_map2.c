#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include "../includes/get_next_line/get_next_line.h"

void	check_player(t_cube *cube, char *line, int i)
{
	if (is_player(line) > 0)
	{
		cube->player_x = is_player(line) + 1;
		cube->player_y = i;
	}
}

void	set_map_array(t_cube *cube, t_file *file)
{
	int		i;
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
	i = 1;
	while (i < cube->map_length + 1)
	{
		line = get_line(file);
		check_player(cube, line, i);
		ft_memcpy(cube->map[i] + 1, line, ft_strlen(line));
		ft_memcpy(cube->cpy_map[i] + 1, line, ft_strlen(line));
		free(line);
		i++;
	}
}

int	parse_map_element(t_cube *cube, t_file *file)
{
	char	*line;

	line = empty_line_read(file);
	calculate_map_length(cube, file, line);
	close(file->file_fd);
	open_cub_file(file);
	set_map_array(cube, file);
	cube->map_length++;
	cube->map_width++;
	validate_map(cube);
	return (0);
}
