#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>

int init_walls(t_vars *vars)
{
	vars->cube->no_wall = mlx_load_png(vars->cube->no);
	return 0;
}

int	init_struct(t_vars *vars)
{
	// cube->ceilling_rgb[0] = 1;
	// cube->ceilling_rgb[1] = 1;
	// cube->ceilling_rgb[2] = 1;
	// cube->floor_rgb[0] = 255;
	// cube->floor_rgb[1] = 255;
	// cube->floor_rgb[2] = 255;
	int32_t floor;
	floor = 0xff5db812;
	int32_t ceilling_c;
	ceilling_c = 0xffdb9f5a;
	int32_t green;
	green = 0xff00ff00;
	vars->mlx = mlx_init(vars->cube->window_x, vars->cube->window_y, "MLX42", true);
	vars->cube->g_img_floor = mlx_new_image(vars->mlx, 1000, 500);
	vars->cube->g_img_ceilling = mlx_new_image(vars->mlx, 1000, 500);
	
	vars->cube->g_img_demo = mlx_new_image(vars->mlx, 100, 100);
	ft_memset32(vars->cube->g_img_demo->pixels, green , vars->cube->g_img_demo->width * vars->cube->g_img_demo->height);
	
	ft_memset32(vars->cube->g_img_floor->pixels, floor , vars->cube->g_img_floor->width * vars->cube->g_img_floor->height);
	ft_memset32(vars->cube->g_img_ceilling->pixels, ceilling_c , vars->cube->g_img_ceilling->width * vars->cube->g_img_ceilling->height);
	
	
	mlx_image_to_window(vars->mlx, vars->cube->g_img_ceilling, 0, 0);
	mlx_image_to_window(vars->mlx, vars->cube->g_img_floor, 0, 500);
	mlx_image_to_window(vars->mlx, vars->cube->g_img_demo, 0, 0);
	return (0);
}