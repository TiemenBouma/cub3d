#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>

#include <stdio.h>

int init_walls(t_cube *cube, mlx_t *mlx)
{
	cube->texture_no_wall = mlx_load_png(cube->no);//("pics/greystone.png");//
	if (cube->texture_no_wall == NULL)
		error_msg_exit("Error: North wall sprite error.\n", 1);
	cube->g_img_wall_demo = mlx_texture_to_image(mlx, cube->texture_no_wall);
	mlx_image_to_window(mlx, cube->g_img_wall_demo, 0, 500);

	cube->texture_ea_wall = mlx_load_png(cube->ea);//("pics/greystone.png");//
	if (cube->texture_ea_wall == NULL)
		error_msg_exit("Error: East wall sprite error.\n", 1);
	cube->g_img_wall_demo = mlx_texture_to_image(mlx, cube->texture_ea_wall);
	mlx_image_to_window(mlx, cube->g_img_wall_demo, 100, 500);

	cube->texture_so_wall = mlx_load_png(cube->so);//("pics/greystone.png");//
	if (cube->texture_so_wall == NULL)
		error_msg_exit("Error: South wall sprite error.\n", 1);
	cube->g_img_wall_demo = mlx_texture_to_image(mlx, cube->texture_so_wall);
	mlx_image_to_window(mlx, cube->g_img_wall_demo, 200, 500);

	cube->texture_we_wall = mlx_load_png(cube->we);//("pics/greystone.png");//
	if (cube->texture_we_wall == NULL)
		error_msg_exit("Error: West wall sprite error.\n", 1);
	cube->g_img_wall_demo = mlx_texture_to_image(mlx, cube->texture_we_wall);
	mlx_image_to_window(mlx, cube->g_img_wall_demo, 300, 500);
	return 0;
}

int	make_floor_ceilling(t_cube *cube)
{
	
}

mlx_t	*init_mlx_stuff(t_cube *cube)
{
	mlx_t	*mlx;
	// cube->ceilling_rgb[0] = 1;
	// cube->ceilling_rgb[1] = 1;
	// cube->ceilling_rgb[2] = 1;
	// cube->floor_rgb[0] = 255;
	// cube->floor_rgb[1] = 255;
	// cube->floor_rgb[2] = 255;
	int32_t floor;
	floor = get_rgba(cube->floor_rgb[0] ,cube->floor_rgb[1] , cube->floor_rgb[2] ,255);
	//floor = 0xff5db812;
	int32_t ceilling_c;
	ceilling_c = 0xffdb9f5a;
	int32_t green;
	green = 0xff00ff00;
	mlx = mlx_init(cube->window_x, cube->window_y, "MLX42", true);
	cube->g_img_floor = mlx_new_image(mlx, 1000, 500);
	cube->g_img_ceilling = mlx_new_image(mlx, 1000, 500);
	cube->g_img_demo = mlx_new_image(mlx, 100, 100);

	make_floor_ceilling(cube);
	ft_memset32(cube->g_img_demo->pixels, green , cube->g_img_demo->width * cube->g_img_demo->height);
	
	ft_memset32(cube->g_img_floor->pixels, floor , cube->g_img_floor->width * cube->g_img_floor->height);
	ft_memset32(cube->g_img_ceilling->pixels, ceilling_c , cube->g_img_ceilling->width * cube->g_img_ceilling->height);

	
	mlx_image_to_window(mlx, cube->g_img_ceilling, 0, 0);
	mlx_image_to_window(mlx, cube->g_img_floor, 0, 500);
	mlx_image_to_window(mlx, cube->g_img_demo, 0, 0);
	init_walls(cube, mlx);
	return (mlx);
}
