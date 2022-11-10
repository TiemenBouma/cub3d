#include <stdlib.h>
#include "../includes/libft/libft.h"
#include "../includes/cub3d.h"
#include "../includes/get_next_line/get_next_line.h"

void	*ft_memset32(void *str, int32_t c, int32_t len)
{
	int32_t	i;
	int32_t	*ptr;

	ptr = (int32_t *)str;
	i = 0;
	while (i < len)
	{
		ptr[i] = (int32_t)c;
		i++;
	}
	return (ptr);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	error_msg_exit(char * msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	exit (exit_code);
}

char	*get_line(t_file *file)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	line = get_next_line(file->file_fd);
	if (line == NULL)
		return (NULL);
	while (line[i] != '\0'  && line[i] != '\n')
		i++;
	temp = ft_substr(line, 0, i);
	if (temp == NULL)
		error_msg_exit("Error: Malloc error", 1);
	free(line);
	return (temp);
}

int	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (0);
}

void print_map(char **map)
{
	int i = 0;
	while (map[i])
	{
		printf("DEBUG:%s\n", map[i] + 1);
		i++;
	}
}