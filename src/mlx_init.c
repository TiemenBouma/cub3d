#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <stdlib.h>

int	init_walls(t_cube *cube, mlx_t *mlx)
{
	(void)mlx;
	cube->texture_no_wall = mlx_load_png(cube->no);
	if (cube->texture_no_wall == NULL)
		error_msg_exit("Error: North wall sprite error.\n", 1);
	cube->texture_ea_wall = mlx_load_png(cube->ea);
	if (cube->texture_ea_wall == NULL)
		error_msg_exit("Error: East wall sprite error.\n", 1);
	cube->texture_so_wall = mlx_load_png(cube->so);
	if (cube->texture_so_wall == NULL)
		error_msg_exit("Error: South wall sprite error.\n", 1);
	cube->texture_we_wall = mlx_load_png(cube->we);
	if (cube->texture_we_wall == NULL)
		error_msg_exit("Error: West wall sprite error.\n", 1);
	return (0);
}

static void	put_pixel_loop(mlx_image_t *img, uint32_t max_x,
	uint32_t max_y, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < max_x)
	{
		y = 0;
		while (y < max_y)
		{
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	make_floor_ceilling(mlx_t *mlx, t_cube *cube)
{
	int32_t	floor_color;
	int32_t	ceilling_color;

	floor_color = get_rgba(cube->floor_rgb[0], cube->floor_rgb[1],
			cube->floor_rgb[2], 255);
	ceilling_color = get_rgba(cube->ceilling_rgb[0], cube->ceilling_rgb[1],
			cube->ceilling_rgb[2], 255);
	cube->g_img_floor = mlx_new_image(mlx, SCREEN_X, SCREEN_Y / 2);
	cube->g_img_ceilling = mlx_new_image(mlx, SCREEN_X, SCREEN_Y / 2);
	put_pixel_loop(cube->g_img_floor, SCREEN_X, SCREEN_Y / 2, floor_color);
	put_pixel_loop(cube->g_img_ceilling, SCREEN_X, SCREEN_Y / 2,
		ceilling_color);
	mlx_image_to_window(mlx, cube->g_img_floor, 0, SCREEN_Y / 2);
	mlx_image_to_window(mlx, cube->g_img_ceilling, 0, 0);
}

mlx_t	*init_mlx_stuff(t_cube *cube)
{
	mlx_t	*mlx;

	mlx = mlx_init(cube->window_x, cube->window_y, "MLX42", true);
	make_floor_ceilling(mlx, cube);
	init_walls(cube, mlx);
	cube->g_img_DEMO = mlx_new_image(mlx, SCREEN_X, SCREEN_Y);
	return (mlx);
}
