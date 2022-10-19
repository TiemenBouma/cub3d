#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

int	parsing(t_vars *vars)
{
	int fd;
	//char	*line;

	vars->cube->file_name = vars->cube->argv[1];
	fd = open(vars->cube->file_name, O_RDONLY);
	//gnl

	vars->cube->no = ft_strdup("greystone.png");
	vars->cube->ea = ft_strdup("greystone.png");
	vars->cube->so = ft_strdup("greystone.png");
	vars->cube->we = ft_strdup("greystone.png");
	return 0;
}