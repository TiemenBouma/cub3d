#include "includes/MLX42/include/MLX42/MLX42.h"
#include "includes/cub3d.h"
#include <stdlib.h>

// void	key_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_vars	*vars;

// 	vars = param;
// 	if (keydata.action == MLX_PRESS)

// }

void	hook(void *param)
{
	t_vars	*vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		vars->cube->g_img_demo->instances[0].y -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		vars->cube->g_img_demo->instances[0].y += 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		vars->cube->g_img_demo->instances[0].x -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		vars->cube->g_img_demo->instances[0].x += 5;
}


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

int	game_loop_mlx(t_vars *vars)
{
	//vars->mlx = mlx_init(vars->cube->window_x, vars->cube->window_y, "MLX42", true);
	if (!vars->mlx)
		exit(EXIT_FAILURE);
	//init_mlx_map(vars);
	//mlx_key_hook(vars->mlx, key_hook, vars);
	mlx_loop_hook(vars->mlx, &hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
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

int main(void)
{
	t_vars	vars;
	t_cube	cube;

	int32_t color;
	color = 0xff0000ff;
	vars.cube = &cube;
	cube.window_x = 1000;
	cube.window_y = 1000;
	init_struct(&vars);
	game_loop_mlx(&vars);

	return (0);
}