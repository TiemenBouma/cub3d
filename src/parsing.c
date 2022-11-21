/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:41:33 by tiemen            #+#    #+#             */
/*   Updated: 2022/11/21 13:38:15 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#define ELEMENTS_COUNT 6

void	set_element(char **split, char **cube_element)
{
	if (*cube_element != NULL)
		error_msg_exit("Error: Duplicate element.\n", 1);
	*cube_element = ft_strdup(split[1]);
}

int	lookup_element(t_cube *cube, char **split, char *line)
{
	if (split == NULL)
		error_msg_exit("Error: Split error", 1);
	else if (split[0] == NULL)
	{
		free_double_ptr(split);
		free(line);
		return (1);
	}
	else if (split[1] == NULL)
		error_msg_exit("Error: no valid Element.\n", 1);
	else if (ft_strncmp(split[0], "NO", 3) == 0)
		set_element(split, &cube->no);
	else if (ft_strncmp(split[0], "EA", 3) == 0)
		set_element(split, &cube->ea);
	else if (ft_strncmp(split[0], "SO", 3) == 0)
		set_element(split, &cube->so);
	else if (ft_strncmp(split[0], "WE", 3) == 0)
		set_element(split, &cube->we);
	else if (ft_strncmp(split[0], "F", 2) == 0)
		set_rgb(split[1], cube->floor_rgb);
	else if (ft_strncmp(split[0], "C", 2) == 0)
		set_rgb(split[1], cube->ceilling_rgb);
	else
		error_msg_exit("Error: no valid Element.\n", 1);
	return (0);
}

int	parse_elements(t_cube *cube, t_file *file)
{
	int		i;
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
		{
			free(line);
			continue ;
		}
		split = ft_split(line, ' ');
		if (lookup_element(cube, split, line))
			continue ;
		i++;
		free_double_ptr(split);
		free(line);
	}
	return (0);
}

int	parse_cub_file_lines(t_cube *cube, t_file *file)
{
	parse_elements(cube, file);
	parse_map_element(cube, file);
	return (0);
}

int	parsing(t_vars *vars)
{
	validate_file_name(vars->file);
	open_cub_file(vars->file);
	parse_cub_file_lines(vars->cube, vars->file);
	set_dir_vector(vars->cube->map[(int)vars->cube->player_y]
	[(int)vars->cube->player_x], &vars->pov->dir_x, &vars->pov->dir_y);
	set_plane_vector(vars->cube->map[(int)vars->cube->player_y]
	[(int)vars->cube->player_x], &vars->pov->plane_x, &vars->pov->plane_y);
	return (0);
}
