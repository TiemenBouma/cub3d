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
	// t_pov pov;

	if (argc != 2)
	{
		ft_putstr_fd("Error: No file or more than 1 file specified.\n", 2);
		exit (1);
	}
	vars.pov = malloc(sizeof(t_pov));
	if (vars.pov == NULL)
		error_msg_exit("Error: malloc failure in main.", 1);
	vars.cube = &cube;
	vars.file = &file;
	init_structs(&vars, argv);
	parsing(&cube, &file);
	mlx = init_mlx_stuff(&cube);


	// printf("DEBUG: pos x = %d y = %d\n", cube.player_x, cube.player_y);
	find_playpos(&cube, vars.pov);


	//cube.texture_DEMO = mlx_load_png("pics/greystone.png");
	cube.g_img_DEMO = mlx_new_image(mlx, SCREEN_X, SCREEN_Y);
	cast_rays(&cube, cube.map, vars.pov);
	mlx_image_to_window(mlx, cube.g_img_DEMO, 0, 0);
	
	// demo_scaling(mlx, &cube);
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
