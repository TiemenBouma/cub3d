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
	t_pov	pov;

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
	find_playpos(&cube, &pov);
	vars.pov = &pov;
	//cube.g_img_DEMO = mlx_new_image(mlx, SCREEN_X, SCREEN_Y);
	//cast_rays(&cube, cube.map, &pov);
	//mlx_image_to_window(mlx, cube.g_img_DEMO, 0, 0);
	vars.mlx = mlx;
	game_loop_mlx(&vars);
	return (0);
}
