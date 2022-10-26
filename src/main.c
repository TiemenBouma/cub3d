#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include "../includes/libft/libft.h"
#include <stdlib.h>

#include <stdio.h>



int main(int argc, char **argv)
{
	t_vars	vars;
	t_cube	cube;
	t_file	file;
	mlx_t	*mlx;
	
	if (argc != 2)
	{
		ft_putstr_fd("Error: No file or more than 1 file specified.\n", 2);
		exit (1);
	}
	vars.cube = &cube;
	vars.file = &file;
	init_structs(&vars, argv);
	parsing(&cube, &file);
	mlx = init_mlx_stuff(&cube);
	demo_scaling(mlx, &cube);
	vars.mlx = mlx;
	game_loop_mlx(&vars);

	return (0);
}

// #include "../includes/MLX42/include/MLX42/MLX42.h"
// #include "../includes/cub3d.h"

//  //dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]
 
// int    scaling(mlx_texture_t *texture, mlx_image_t *img, double scale)
// {
//        texture->
// }