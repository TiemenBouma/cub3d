#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <fcntl.h>
#include "../includes/get_next_line/get_next_line.h"

#include <stdio.h>

int	validate_file()
{
 return (0);
}

int	open_sprites(t_vars *vars)
{
	(void)vars;
	return (0);
}

int	parsing(t_vars *vars)
{
	int fd;
	char	*line;
	char	*temp;
	int i;
	i = 0;

	vars->file->file_name = vars->argv[1];
	fd = open(vars->file->file_name, O_RDONLY);
	printf("DEBUG: fd = %d\n", fd);
	//gnl
	line = get_next_line(fd);
	printf("DEBUG: LINE = |%s|\n", line);

	while (line[i] != '\0'  && line[i] != '\n')
	{
	//	printf("DEBUG WHILELOOP\n");
		i++;
	}	
	temp = ft_substr(line, 5, i - 5);
	free(line);
	line = temp;
	printf("DEBUG: LINE = %s\n", line);
	vars->cube->no = ft_strdup(line);
	printf("DEBUG2\n");
	free(line);

	vars->cube->ea = ft_strdup("greystone.png");
	vars->cube->so = ft_strdup("greystone.png");
	vars->cube->we = ft_strdup("greystone.png");
	return 0;
}