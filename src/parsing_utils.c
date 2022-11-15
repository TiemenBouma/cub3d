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
